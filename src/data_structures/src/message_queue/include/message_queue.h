#ifndef LIBCC_DATA_STRUCTURES_MESSAGE_QUEUE_H
#define LIBCC_DATA_STRUCTURES_MESSAGE_QUEUE_H

#include <atomic>
#include <queue>
#include <semaphore>
#include <string>

#include "status_or.h"

using std::atomic_int;
using std::binary_semaphore;
using std::queue;
using std::string;
using ostp::libcc::utils::StatusOr;

namespace ostp::libcc::data_structures {

class MessageQueue {
   public:
    /// Creates a new MessageQueue.
    MessageQueue();

    /// Pushes a message to the queue.
    StatusOr<void> push(const std::string message);

    /// Pops a message from the queue.
    StatusOr<string> pop();

    /// Close the queue.
    void close();

    /// Whether the queue is closed.
    bool is_closed() const;

    /// Whether the queue is empty.
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
