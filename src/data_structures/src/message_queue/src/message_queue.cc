#include "message_queue.h"

using ostp::libcc::data_structures::MessageQueue;
using ostp::libcc::utils::Status;
using ostp::libcc::utils::StatusOr;
using std::string;

/// See message_queue.h for documentation.
MessageQueue::MessageQueue() : messages(), semaphore(0), closed(false) {}

/// See message_queue.h for documentation.
StatusOr<void> MessageQueue::push(const std::string message) {
    // Check if the queue is closed.
    if (closed) {
        return StatusOr<void>(Status::ERROR, "Queue is closed.");
    }

    // Push the message to the queue and signal the semaphore.
    messages.push(message);
    semaphore.release();
    return StatusOr<void>(Status::OK, "Message pushed.");
}

/// See message_queue.h for documentation.
StatusOr<string> MessageQueue::pop() {
    // If the queue is closed and empty, return an empty string.
    if (closed && messages.empty()) {
        return StatusOr<string>(Status::ERROR, "Queue is closed and empty.", "");
    }

    // Wait for a message to be available.
    waiting_threads++;
    semaphore.acquire();
    waiting_threads--;

    // If the queue was closed while waiting and there are no more messages, return an empty string.
    if (closed && messages.empty()) {
        return StatusOr<string>(Status::ERROR, "Queue is closed and empty.", "");
    }

    string message = std::move(messages.front());
    messages.pop();
    return StatusOr<string>(Status::ERROR, "Queue is closed and empty.", std::move(message));
}

/// See message_queue.h for documentation.
void MessageQueue::close() {
    // Mark the queue as closed.
    closed = true;

    // Release all waiting threads.
    for (int i = 0; i < waiting_threads; i++) {
        semaphore.release();
    }
}

/// See message_queue.h for documentation.
bool MessageQueue::is_closed() const { return closed; }

/// See message_queue.h for documentation.
bool MessageQueue::empty() const { return messages.empty(); }
