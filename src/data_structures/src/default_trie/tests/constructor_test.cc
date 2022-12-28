#include "default_trie.h"

using ostp::libcc::data_structures::DefaultTrie;

const int _no_match = -1;
const int _match = 1;

/// Tests whether the default value is returned when the key is not found.
int main()
{
    // The root node should return the specified root return value.
    DefaultTrie<char, int> trie(_no_match, _match);
    if (trie.get("", 0) != _match)
    {
        return 1;
    }

    // The root node should return the specified default return value if no value is specified.
    DefaultTrie<char, int> trie2(_no_match);
    if (trie2.get("", 0) != _no_match)
    {
        return 1;
    }

    return 0;
}