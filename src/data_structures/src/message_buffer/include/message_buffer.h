#ifndef LIBCC_DATA_STRUCTURES_MESSAGE_BUFFER_H
#define LIBCC_DATA_STRUCTURES_MESSAGE_BUFFER_H

#include <inttypes.h>

#include <atomic>
#include <future>
#include <memory>
#include <queue>
#include <semaphore>
#include <optional>
#include <string>
#include <vector>

#include "absl/status/status.h"

using std::atomic_int;
using std::binary_semaphore;
using std::future;
using std::future_status;
using std::queue;
using std::string;
using std::vector;

namespace ostp::libcc::data_structures {

/// A thread-safe message buffer that implements the producer-consumer pattern.
///
/// The queue is initially open and can be closed by calling the close() method. Once the queue is
/// closed, no more messages can be pushed to it.
template <typename T>
class MessageBuffer {
   public:
    /// Creates a new MessageBuffer.
    MessageBuffer() : messages(), semaphore(0), waiting_threads(0), closed(false) {}

    /// Pushes a message to the queue.
    ///
    /// Arguments:
    ///     message: The message to push.
    ///
    /// Returns:
    ///     OK if the message was pushed successfully.
    ///     CLOSED if the queue is closed.
    absl::Status push(T &&message) {
        // Check if the queue is closed.
        if (closed) {
            return absl::CancelledError("Queue is closed.");
        }

        // Push the message to the queue and signal the semaphore.
        messages.push(std::move(message));

        // If there are threads waiting, signal one of them.
        semaphore.release();

        // Return OK.
        return absl::OkStatus();
    }

    /// Pops a message from the queue.
    ///
    /// If the queue is empty but not closed, this method blocks until a message is pushed to the
    /// queue or the queue is closed.
    ///
    /// Arguments:
    ///     None.
    ///
    /// Returns:
    ///     OK if the message was popped successfully and the message is returned.
    ///     CLOSED if the queue is closed and the message is returned.
    ///     EMPTY if the queue is empty and closed.
    std::pair<absl::Status, std::optional<T>> pop() {
        // If the queue is closed and empty, return an empty string.
        if (closed && messages.empty()) {
            return {absl::CancelledError("Queue is closed and empty."), std::nullopt};
        }

        // Wait for a message to be available.
        waiting_threads++;
        semaphore.acquire();
        waiting_threads--;

        // If the queue was closed while waiting and there are no more messages, return an empty
        // string.
        if (closed && messages.empty()) {
            return {absl::CancelledError("Queue is closed and empty."), std::nullopt};
        }

        // Pop the message from the queue.
        const auto message = std::move(messages.front());
        messages.pop();

        // Return the message.
        return {absl::OkStatus(), std::move(message)};
    }

    /// Pops a message from the queue with a timeout.
    ///
    /// If the queue is empty but not closed, this method blocks until a message is pushed to the
    /// queue, the queue is closed or the timeout is reached. If the timeout is reached, the method
    /// closes the queue and returns an empty string.
    ///
    /// Arguments:
    ///     timeout: The timeout in milliseconds.
    ///
    /// Returns:
    ///     OK if the message was popped successfully and the message is returned.
    ///     TIMEOUT if the timeout was reached.
    ///     CLOSED if the queue is closed and the message is returned.
    ///     EMPTY if the queue is empty and closed.
    std::pair<absl::Status, std::optional<T>> pop(int timeout) {
        // Try to pop a message with the pop() method without a timeout.
        auto future = std::async(
            std::launch::async,
            static_cast<std::pair<absl::Status, std::optional<T>> (MessageBuffer::*)()>(&MessageBuffer::pop),
            this);

        // Wait until the future is ready or the timeout is reached.
        future_status status = future.wait_for(std::chrono::milliseconds(timeout));

        // Return the result of the future if it is ready or a timeout error.
        if (status == future_status::ready) {
            return std::move(future.get());
        } else {
            close();
            return {absl::DeadlineExceededError("Timeout reached."), std::nullopt};
        }
    }

    /// Closes the queue.
    ///
    /// If the queue is already closed, this method does nothing.
    ///
    /// Arguments:
    ///     None.
    ///
    /// Returns:
    ///     None.
    void close() {
        // Mark the queue as closed.
        closed = true;

        // Release all waiting threads.
        for (int i = 0; i < waiting_threads; i++) {
            semaphore.release();
        }
    }

    // Getters.

    /// Returns the number of messages in the queue or -(number of threads waiting on the queue).
    ///
    /// Arguments:
    ///     None.
    ///
    /// Returns:
    ///     OK if the queue is not closed and the number of messages is returned or -(number of
    ///        threads waiting on the queue).
    ///     CLOSED if the queue is closed and the number of messages is returned or minus the number
    //             of threads waiting.
    std::pair<absl::Status, int> size() const {
        // If the message que is not closed return the number of message available or minus
        // the number of thread blocked.
        return {closed ? absl::CancelledError("Queue is closed.") : absl::OkStatus(),
                closed ? -waiting_threads : messages.size()};
    }

    /// Returns whether the queue is closed.
    bool is_closed() const { return closed; }

    /// Returns whether the queue is empty.
    bool empty() const { return messages.empty(); }

   private:
    // Attributes.

    /// The queue of messages.
    queue<T> messages;

    /// The semaphore used to synchronize the queue.
    binary_semaphore semaphore;

    /// The number of threads waiting on the semaphore.
    atomic_int waiting_threads;

    /// Whether the queue is closed.
    bool closed;
};

}  // namespace ostp::libcc::data_structures

#endif
