#include "default_trie.h"

using ostp::libcc::data_structures::DefaultTrie;

const int _no_match = -1;
const int _match = 1;
const int _match_2 = 2;

/// Tests whether the default value is returned when the key is not found.
int main()
{
    // The root node should return the specified root return value.
    DefaultTrie<char, int> trie(_no_match, _match);

    // After adding a key, the trie should return the specified return value for that key.
    if (trie.get("abc", 3) != _no_match)
    {
        return 1;
    }

    trie.add("abc", 3, _match);

    if (trie.get("abc", 3) != _match)
    {
        return 1;
    }

    // After re-inserting a key, the trie should return the specified return value for that key.
    trie.add("abc", 3, _match_2);

    if (trie.get("abc", 3) != _match_2)
    {
        return 1;
    }

    // Keys can share prefixes.
    trie.add("ab", 2, _match);
    trie.add("abcd", 4, _match);

    if (trie.get("ab", 2) != _match || trie.get("abc", 3) != _match_2 ||
        trie.get("abcd", 4) != _match)
    {
        return 1;
    }

    return 0;
}