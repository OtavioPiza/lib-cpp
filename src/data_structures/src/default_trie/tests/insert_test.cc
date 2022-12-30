#include "default_trie.h"
#include "logger.h"

using ostp::libcc::data_structures::DefaultTrie;
using ostp::libcc::utils::log_error;
using ostp::libcc::utils::log_success;

const char *_sender = "default_trie_insert_test";
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
        log_error("The trie should return the default value when the key is not found.", _sender);
        return 1;
    }

    trie.insert("abc", 3, _match);

    if (trie.get("abc", 3) != _match)
    {
        log_error("The trie should return the specified value when the key is found.", _sender);
        return 1;
    }

    // After re-inserting a key, the trie should return the specified return value for that key.
    trie.insert("abc", 3, _match_2);

    if (trie.get("abc", 3) != _match_2)
    {
        log_error("The trie should return the specified value when the key is found.", _sender);
        return 1;
    }

    // Keys can share prefixes.
    trie.insert("ab", 2, _match);
    trie.insert("abcd", 4, _match);

    if (trie.get("ab", 2) != _match || trie.get("abc", 3) != _match_2 ||
        trie.get("abcd", 4) != _match)
    {
        log_error("The trie should return the correct value for keys with shared prefixes.", _sender);
        return 1;
    }

    return 0;
}