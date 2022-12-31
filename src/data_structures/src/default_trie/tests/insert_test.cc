#include <sstream>
#include <string>

#include "default_trie.h"
#include "logger.h"

using ostp::libcc::data_structures::DefaultTrie;
using ostp::libcc::utils::log_error;
using std::stringstream;

const char *_sender = "default_trie_insert_test";
const int _no_match = -1;
const int _match = 1;
const int _match_2 = 2;

/// Tests whether the default value is returned when the key is not found.
int main()
{
    stringstream error_stream;
    int error_count = 0;

    // The root node should return the specified root return value.
    DefaultTrie<char, int> trie(_no_match);

    // After adding a key, the trie should return the specified return value for that key.
    if (trie.get("abc", 3) != _no_match)
    {
        error_stream << ++error_count
                     << ". The trie should return the default value when the key is not found."
                     << "FATAL\n";
        log_error(error_stream.str().c_str(), _sender);
        return 1;
    }

    trie.insert("abc", 3, _match);

    if (trie.get("abc", 3) != _match)
    {
        error_stream << ++error_count
                     << ". The trie should return the specified value when the key is found.\n";
    }

    // After re-inserting a key, the trie should return the specified return value for that key.
    trie.insert("abc", 3, _match_2);

    if (trie.get("abc", 3) != _match_2)
    {
        error_stream << ++error_count
                     << ". The trie should return the updated value of the key.\n";
    }

    // Keys can share prefixes.
    trie.insert("ab", 2, _match);
    trie.insert("abcd", 4, _match);

    if (trie.get("ab", 2) != _match || trie.get("abc", 3) != _match_2 ||
        trie.get("abcd", 4) != _match)
    {
        error_stream << ++error_count
                     << ". Shared prefixes should not affect key value.\n";
    }

    // Print errors if any or return.
    if (error_count)
    {
        log_error(error_stream.str().c_str(), _sender);
        return 1;
    }
    return 0;
}