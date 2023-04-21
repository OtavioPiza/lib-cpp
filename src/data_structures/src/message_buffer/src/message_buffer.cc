#include "message_buffer.h"

#include <future>

using ostp::libcc::data_structures::MessageBuffer;
using ostp::libcc::utils::Status;
using ostp::libcc::utils::StatusOr;
using std::future;
using std::future_status;
using std::string;

// Constructors

/// See message_buffer.h for documentation.
MessageBuffer::MessageBuffer() : messages(), semaphore(0), closed(false) {}

// Methods

/// See message_buffer.h for documentation.
StatusOr<void> MessageBuffer::push(const std::string message) {
    // Check if the queue is closed.
    if (closed) {
        return StatusOr<void>(Status::CLOSED, "Queue is closed.");
    }

    // Push the message to the queue and signal the semaphore.
    messages.push(message);

    // If there are threads waiting, signal one of them.
    semaphore.release();

    // Return OK.
    return StatusOr<void>(Status::OK, "Message pushed.");
}

/// See message_buffer.h for documentation.
StatusOr<const string> MessageBuffer::pop() {
    // If the queue is closed and empty, return an empty string.
    if (closed && messages.empty()) {
        return StatusOr<const string>(Status::EMPTY, "Queue is closed and empty.", "");
    }

    // Wait for a message to be available.
    waiting_threads++;
    semaphore.acquire();
    waiting_threads--;

    // If the queue was closed while waiting and there are no more messages, return an empty string.
    if (closed && messages.empty()) {
        return StatusOr<const string>(Status::EMPTY, "Queue was closed and is empty.", "");
    }

    // Pop the message from the queue.
    const string message = std::move(messages.front());
    messages.pop();

    // Return the message.
    return StatusOr<const string>(closed ? (Status::CLOSED) : (Status::OK), "Message popped.",
                                  std::move(message));
}

/// See message_buffer.h for documentation.
StatusOr<const string> MessageBuffer::pop(int timeout) {
    // Try to pop a message with the pop() method without a timeout.
    future<StatusOr<const string>> future = std::async(
        std::launch::async,
        static_cast<StatusOr<const string> (MessageBuffer::*)()>(&MessageBuffer::pop), this);

    // Wait until the future is ready or the timeout is reached.
    future_status status = future.wait_for(std::chrono::milliseconds(timeout));

    // Return the result of the future if it is ready or a timeout error.
    if (status == future_status::ready) {
        return std::move(future.get());
    } else {
        close();
        return StatusOr<const string>(Status::TIMEOUT, "Timeout reached.", "");
    }
}

/// See message_buffer.h for documentation.
void MessageBuffer::close() {
    // Mark the queue as closed.
    closed = true;

    // Release all waiting threads.
    for (int i = 0; i < waiting_threads; i++) {
        semaphore.release();
    }
}

// Getters

/// See message_buffer.h for documentation.
StatusOr<int> MessageBuffer::size() const {
    // If the message que is not closed return the number of message available or minus
    // the number of thread blocked.
    return StatusOr<int>(closed ? Status::CLOSED : Status::OK, "",
                         messages.empty() ? -waiting_threads : messages.size());
}

/// See message_buffer.h for documentation.
bool MessageBuffer::is_closed() const { return closed; }

/// See message_buffer.h for documentation.
bool MessageBuffer::empty() const { return messages.empty(); }
