#ifndef default_trie
#define default_trie

#include <vector>
#include <unordered_map>

#include "default_trie_node.h"

namespace ostp::libcc
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

} // namespace ostp::libcc

#endif
