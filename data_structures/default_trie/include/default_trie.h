#ifndef default_trie
#define default_trie

#include <vector>
#include <unordered_map>

#include "default_trie_node.h"

namespace ostp::libcc::data_structures
{
    /// Default trie data structure.
    template <class K, class R>
    class DefaultTrie
    {
    private:
        const R default_return;        // Default return for no matches.
        std::vector<R> results;        // Vector of returns for each match in the trie.
        std::vector<TrieNode<K>> trie; // Trie data structure.

    public:
        /// Constructs a trie with the specified default return for no matches.
        ///
        /// Arguments:
        ///     default_return: The default return for no matches.
        ///     root_return: The return for the root node.
        DefaultTrie(const R default_return, const R root_return) : default_return(default_return)
        {
            // Add the root node to the trie.
            TrieNode<K> root;
            root.res = results.size();
            results.push_back(root_return);
            trie.push_back(root);
        }

        /// Constructs a trie with the specified default return for no matches and for the root node.
        ///
        /// Arguments:
        ///     default_return: The default return for no matches and for the root node.
        DefaultTrie(const R default_return) : DefaultTrie(default_return, default_return) {}

        /// Adds the specfied entry to the trie with the specified return.
        ///
        /// Arguments:
        ///     entry: The entry to add to the trie.
        ///     entry_len: The length of the entry.
        ///     entry_return: The return for the entry.
        void add(const K entry[], const int entry_len, const R entry_return)
        {
            // Traverse the trie until we reach the end of the entry or a node with no next entry.
            int node = 0;
            for (int i = 0; i < entry_len; i++)
            {
                // Create a new node if there is no next entry.
                if (trie[node].next.find(entry[i]) == trie[node].next.end())
                {
                    trie[node].next[entry[i]] = trie.size();
                    TrieNode<K> new_node;
                    new_node.res = NO_MATCH;
                    trie.push_back(new_node);
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
        ///
        /// Arguments:
        ///     entry: The entry to remove from the trie.
        ///     entry_len: The length of the entry.
        void remove(const K entry[], const int entry_len)
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
        ///
        /// Arguments:
        ///     entry: The entry to get the return for.
        ///     entry_len: The length of the entry.
        R get(const K entry[], const int entry_len)
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

} // namespace ostp::libcc::data_structures

#endif
