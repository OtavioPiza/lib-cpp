#ifndef THREAD_LIST_H
#define THREAD_LIST_H

#include <mutex>
#include <thread>
#include <type_traits>

#include "thread_list_node.h"

using ostp::libcc::data_structures::ThreadListNode;

namespace ostp::libcc::data_structures
{
    /// A list of threads.
    template <typename F>
    class ThreadList
    {
    public:
        /// Constructs a thread list.
        ThreadList();

        /// Destroys a thread list.
        ~ThreadList();

        /// Starts a new thread with the async API and adds it to the list.
        void start_thread(F func)
        {
            // Lock the mutex to find space in the list.
            std::lock_guard<std::mutex> lock(m_mutex);

            
        }

    private:
        std::vector<ThreadListNode<std::result_of<F>::type>> m_thread_list;
        std::vector<int> m_free_list;
        std::mutex m_mutex;
    };

} // namespace ostp::libcc::data_structures

#endif
