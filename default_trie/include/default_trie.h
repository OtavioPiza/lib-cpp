#ifndef default_trie
#define default_trie

#include <vector>
#include <unordered_map>
#include "../src/default_trie.h"

namespace lib_cc
{
    template <typename K, typename R>
    class DefaultTrie
    {
    private:
        std::vector<R> results; // Vector of returns for each match in the trie.
        std::vector<TrieNode<K>> trie;

    public:
        /// Constructs a trie with the specified default return for no matches.
        DefaultTrie(R default_return);

        /// Adds the specfied entry to the trie with the specified return.
        void add(K entry[], int entry_len, R entry_return);
    };

} // namespace lib_cpp

#endif
