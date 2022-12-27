#ifndef default_trie
#define default_trie

#include <vector>
#include <unordered_map>

#include "default_trie_node.h"

namespace ostp::libcc
{
    /// Default trie data structure.
    template <class K, class R>
    class DefaultTrie
    {
    private:
        R default_return;              // Default return for no matches.
        std::vector<R> results;        // Vector of returns for each match in the trie.
        std::vector<TrieNode<K>> trie; // Trie data structure.

    public:
        /// Constructs a trie with the specified default return for no matches.
        DefaultTrie(R default_return)
        {
            this.default_return = default_return;
            this.trie = new std::vector<TrieNode<K>>();
            this.results = new std::vector<R>();
        }

        /// Adds the specfied entry to the trie with the specified return.
        void add(K entry[], int entry_len, R entry_return)
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

            // If there is already a return for the match ending in the last node, replace it otherwise
            // add it to the results vector.
            if (trie[node].res != NO_MATCH)
            {
                results[trie[node].res] = entry_return;
                return;
            }
            else
            {
                trie[node].res = results.size();
                results.push_back(entry_return);
            }
        }

        /// Removes the specified entry from the trie.
        void remove(K entry[], int entry_len)
        {
            // Traverse the trie until we reach the end of the entry or a node with no next entry.
            int node = 0;
            for (int i = 0; i < entry_len; i++)
            {
                // Return if there is no next entry.
                if (trie[node].next.find(entry[i]) == trie[node].next.end())
                {
                    return;
                }

                // Move to the next node.
                node = trie[node].next[entry[i]];
            }

            // If there is a return for the match ending in the last node, remove it.
            if (trie[node].res != NO_MATCH)
            {
                results[trie[node].res] = NO_MATCH;
            }
        }

        /// Returns the return for the longest match in the trie for the specified entry.
        R get(K entry[], int entry_len)
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
    };

} // namespace ostp::libcc

#endif
