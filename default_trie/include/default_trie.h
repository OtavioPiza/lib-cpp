#ifndef default_trie
#define default_trie

#include <vector>
#include <unordered_map>

namespace ostp::lib_cc
{
    /// Default trie data structure.
    template <typename K, typename R>
    class DefaultTrie
    {
    private:
        R default_return;              // Default return for no matches.
        std::vector<R> results;        // Vector of returns for each match in the trie.
        std::vector<TrieNode<K>> trie; // Trie data structure.

    public:
        /// Constructs a trie with the specified default return for no matches.
        DefaultTrie(R default_return);

        /// Adds the specfied entry to the trie with the specified return.
        void add(K entry[], int entry_len, R entry_return);

        /// Removes the specified entry from the trie.
        void remove(K entry[], int entry_len);

        /// Returns the return for the longest match in the trie for the specified entry.
        R get(K entry[], int entry_len);
    };

    /// Node in the default trie data structure.
    ///
    /// Stores the next entries in the trie in an unordered map and the index of the return for
    /// the match ending in this node or NO_MATCH if there isn't one.
    ///
    /// The specified type K must have a hash function defined for it.
    template <typename K>
    class TrieNode
    {
        /// Next entries in the trie.
        std::unordered_map<K, int> next;

        /// Index of the return for the match ending in this node or NO_MATCH if there isn't one.
        int res;
    };

} // namespace ostp::lib_cc

#endif
