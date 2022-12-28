#include "default_trie.h"

using ostp::libcc::data_structures::DefaultTrie;

const int _no_match = -1;
const int _match = 1;

/// Tests whether the default value is returned when the key is not found.
int main()
{
    DefaultTrie<char, int> trie(_no_match, _match);

    // Empty trie should return default value.
    if (trie.get("abc", 3) != _no_match)
    {
        return 1;
    }

    // Empty trie should match empty key.
    if (trie.get("", 0) != _match)
    {
        return 1;
    }

    trie.add("ab", 2, 1);
    trie.add("bc", 2, 2);

    // Trie should return default value for non-existent key.
    if (trie.get("abc", 3) != _no_match)
    {
        return 1;
    }

    // Trie should match existing keys.
    if (trie.get("ab", 2) != _match && trie.get("bc", 2) != _match)
    {
        return 1;
    }

    // Trie should match empty key.
    if (trie.get("", 0) != _match)
    {
        return 1;
    }

    return 0;
}