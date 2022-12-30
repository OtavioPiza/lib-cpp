#include "default_trie.h"

using ostp::libcc::data_structures::DefaultTrie;

const int _no_match = -1;
const int _match = 1;

/// Tests whether the default value is returned when the key is not found.
int main()
{
    // The root node should return the specified root return value.
    DefaultTrie<char, int> trie(_no_match, _match);
    trie.insert("a", 1, _match);
    trie.insert("ab", 2, _match);
    trie.insert("abc", 3, _match);

    // Removing a key works.
    trie.remove("ab", 2);
    if (trie.get("ab", 2) != _no_match)
    {
        return 1;
    }

    // Neither the children or parents are removed.
    if (trie.get("abc", 3) != _match || trie.get("a", 1) != _match)
    {
        return 1;
    }

    return 0;
}