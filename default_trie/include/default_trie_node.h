#ifndef default_trie_node
#define default_trie_node
#define NO_MATCH -1

#include <vector>
#include <unordered_map>

namespace ostp::libcc
{
    /// Node in the default trie data structure.
    ///
    /// Stores the next entries in the trie in an unordered map and the index of the return for
    /// the match ending in this node or NO_MATCH if there isn't one.
    ///
    /// The specified type K must have a hash function defined for it.
    template <class K>
    class TrieNode
    {
        /// Next entries in the trie.
        std::unordered_map<K, int> next;

        /// Index of the return for the match ending in this node or NO_MATCH if there isn't one.
        int res;
    };

} // namespace ostp::libcc

#endif
