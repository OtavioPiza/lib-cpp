#include "default_trie.h"

using ostp::libcc::data_structures::DefaultTrie;

const int _no_match_1 = -1;
const int _no_match_2 = -2;

/// Tests whether the default value is returned when the key is not found.
int main()
{
    // The root node should return the specified root return value.
    DefaultTrie<char, int> trie(_no_match_1);

    // No match should be the one specified in the constructor at first.
    if (trie.get("", 0) != _no_match_1)
    {
        return 1;
    }

    // After updating the default return value, the new value should be returned.
    trie.update_default_return(_no_match_2);
    if (trie.get("", 0) != _no_match_2)
    {
        return 1;
    }

    return 0;
}
