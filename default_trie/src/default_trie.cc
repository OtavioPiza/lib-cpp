#include "../include/default_trie.h"
#include "constants.h"

namespace ostp::lib_cc
{
    // See default_trie.h for documentation.
    template <typename K, typename R>
    DefaultTrie<K, R>::DefaultTrie(R default_return)
    {
        this.default_return = default_return;
        this.trie = new std::vector<TrieNode<K>>();
        this.results = new std::vector<R>();
    }

    // See default_trie.h for documentation.
    template <typename K, typename R>
    void DefaultTrie<K, R>::add(K entry[], int entry_len, R entry_return)
    {
        // Traverse the trie until we reach the end of the entry or a node with no next entry.
        int node = 0;
        for (int i = 0; i < entry_len; i++)
        {
            // Create a new node if there is no next entry.
            if (trie[node].next.find(entry[i]) == trie[node].next.end())
            {
                trie[node].next[entry[i]] = trie.size();
                trie.push_back(new TrieNode<K>());
                trie[trie.size() - 1].res = NO_MATCH;
                trie[trie.size() - 1].next = new std::unordered_map<K, int>();
            }

            // Move to the next node.
            node = trie[node].next[entry[i]];
        }

        // Add the return to the results vector and set the node's return index.
        trie[node].res = results.size();
        results.push_back(entry_return);
    }

    // See default_trie.h for documentation.
    template <typename K, typename R>
    R DefaultTrie<K, R>::get(K entry[], int entry_len)
    {
        // Traverse the trie until we reach the end of the entry or a node with no next entry.
        int node = 0;
        for (int i = 0; i < entry_len; i++)
        {
            // Return the default return if there is no next entry.
            if (trie[node].next.find(entry[i]) == trie[node].next.end())
            {
                return default_return;
            }

            // Move to the next node.
            node = trie[node].next[entry[i]];
        }

        // Return the result for the match ending in the last node or the default return if there
        // isn't one.
        if (trie[node].res == NO_MATCH)
        {
            return default_return;
        }
        else
        {
            return results[trie[node].res];
        }
    }

} // namespace ostp::lib_cpp
