#include <sstream>
#include <string>

#include "default_trie.h"
#include "logger.h"

using ostp::libcc::data_structures::DefaultTrie;
using ostp::libcc::utils::log_error;
using std::stringstream;

const char *test_name = "default_trie_constructor_test";
const int _no_match = -1;

/// Tests whether the default value is returned when the key is not found.
int main()
{
    stringstream error_stream;
    int error_count = 0;

    // The root node should return no_match;
    DefaultTrie<char, int> trie2(_no_match);
    if (trie2.get("", 0) != _no_match)
    {
        error_stream << ++error_count << ". The root node should be a no match.\n";
    }

    // Print errors if any or return.
    if (error_count)
    {
        log_error(error_stream.str().c_str(), test_name);
        return 1;
    }
    return 0;
}