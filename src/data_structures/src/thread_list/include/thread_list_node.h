#ifndef THREAD_LIST_NODE_H
#define THREAD_LIST_NODE_H

namespace ostp::libcc::data_structures
{
    template <class R>
    struct ThreadListNode
    {
        /// The future object returned by the async API.
        const std::future<R> future;

        /// The next node in the list or -1 if this is the last node.
        const int next;

        /// The previous node in the list or -1 if this is the first node.
        const int prev;
    };
}

#endif
