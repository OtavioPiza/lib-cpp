#include <sstream>
#include <string>

#include "default_trie.h"
#include "logger.h"

using ostp::libcc::data_structures::DefaultTrie;
using ostp::libcc::utils::log_error;
using std::stringstream;

const char *test_name = "default_trie_get_test";
const int _no_match = -1;
const int _match = 1;

/// Tests whether the default value is returned when the key is not found.
int main()
{
    stringstream error_stream;
    int error_count = 0;

    DefaultTrie<char, int> trie(_no_match);

    // Empty trie should return default value.
    if (trie.get("abc", 3) != _no_match)
    {
        error_stream << ++error_count
                     << ". The trie should return the default value when the key is not found.\n";
    }

    // Empty trie should not match empty key.
    if (trie.get("", 0) != _no_match)
    {
        error_stream << ++error_count
                     << ". The empty string should not match any value on an empty trie.\n";
    }

    trie.insert("ab", 2, 1);
    trie.insert("bc", 2, 2);

    // Trie should return default value for non-existent key.
    if (trie.get("abc", 3) != _no_match)
    {
        error_stream << ++error_count
                     << ". The trie should return the default value when the key is not found.\n";
    }

    // Trie should match existing keys.
    if (trie.get("ab", 2) != _match && trie.get("bc", 2) != _match)
    {
        error_stream << ++error_count
                     << ". The trie should return the correct value for existing keys.\n";
    }

    // Print errors if any or return.
    if (error_count)
    {
        log_error(error_stream.str().c_str(), test_name);
        return 1;
    }
    return 0;
}