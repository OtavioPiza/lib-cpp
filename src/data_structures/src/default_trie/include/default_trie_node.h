#ifndef DEFAULT_TRIE_NODE_H
#define DEFAULT_TRIE_NODE_H
#define NO_MATCH -1

#include <vector>
#include <unordered_map>

namespace ostp::libcc::data_structures
{
    /// Node in the default trie data structure.
    ///
    /// Stores the next entries in the trie in an unordered map and the index of the return for
    /// the match ending in this node or NO_MATCH if there isn't one.
    ///
    /// The specified type K must have a hash function defined for it.
    template <class K>
    struct TrieNode
    {
        /// Index of the return for the match ending in this node or NO_MATCH if there isn't one.
        int res;

        /// Next entries in the trie.
        std::unordered_map<K, int> next;
    };

    /// Specialization of the TrieNode struct for char.
    ///
    /// Stores the next entries in the trie in an array and the index of the return for
    /// the match ending in this node or NO_MATCH if there isn't one.
    template <>
    struct TrieNode<char>
    {
        /// Index of the return for the match ending in this node or NO_MATCH if there isn't one.
        int res;

        /// Next entries in the trie.
        std::vector<char> next;
    };

} // namespace ostp::libcc::data_structures

#endif
