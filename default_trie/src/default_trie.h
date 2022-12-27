#ifndef _default_trie
#define _default_trie

#define NO_MATCH -1

namespace lib_cc
{
    template <typename K>
    class TrieNode
    {
        /// Next entries in the trie.
       std::unordered_map<K, int> next;

        /// Index of the return for the match ending in this node or NO_MATCH if there isn't one.
        int res;
    };
} // namespace lib_cpp

#endif
