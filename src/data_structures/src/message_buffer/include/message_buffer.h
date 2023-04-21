#ifndef LIBCC_DATA_STRUCTURES_MESSAGE_BUFFER_H
#define LIBCC_DATA_STRUCTURES_MESSAGE_BUFFER_H

#include <atomic>
#include <queue>
#include <semaphore>
#include <string>

#include "status_or.h"

using ostp::libcc::utils::StatusOr;
using std::atomic_int;
using std::binary_semaphore;
using std::queue;
using std::string;

namespace ostp::libcc::data_structures {

/// A thread-safe message buffer that implements the producer-consumer pattern.
///
/// The queue is initially open and can be closed by calling the close() method. Once the queue is
/// closed, no more messages can be pushed to it.
class MessageBuffer {
   public:
    /// Creates a new MessageBuffer.
    MessageBuffer();

    /// Pushes a message to the queue.
    ///
    /// Arguments:
    ///     message: The message to push.
    ///
    /// Returns:
    ///     OK if the message was pushed successfully.
    ///     CLOSED if the queue is closed.
    StatusOr<void> push(const string message);

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
    StatusOr<const string> pop();

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
    StatusOr<const string> pop(int timeout);

    /// Closes the queue.
    ///
    /// If the queue is already closed, this method does nothing.
    ///
    /// Arguments:
    ///     None.
    ///
    /// Returns:
    ///     None.
    void close();

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
    StatusOr<int> size() const;

    /// Returns whether the queue is closed.
    bool is_closed() const;

    /// Returns whether the queue is empty.
    bool empty() const;

   private:
    // Attributes.

    /// The queue of messages.
    queue<string> messages;

    /// The semaphore used to synchronize the queue.
    binary_semaphore semaphore;

    /// The number of threads waiting on the semaphore.
    atomic_int waiting_threads;

    /// Whether the queue is closed.
    bool closed;
};

}  // namespace ostp::libcc::data_structures

#endif
