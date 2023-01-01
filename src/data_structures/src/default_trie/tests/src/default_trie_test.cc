#include <sstream>
#include <string>

#include "default_trie.h"
#include "logger.h"
#include "testing.h"

using ostp::libcc::data_structures::DefaultTrie;
using ostp::libcc::utils::log_error;
using std::stringstream;

const int no_match = -1;

START_SUITE(DefaultTrie_Constructor)

START_TEST(EmptyStringShouldHaveNoMatch)
{
    DefaultTrie<char, int> trie(no_match);

    // The trie should be empty and have no matches even for empty strings.
    TEST(trie.get("", 0) == no_match);
}
END_TEST

START_TEST(DefaultTrie_Get)
{
    DefaultTrie<char, int> trie(no_match);

    // Empty trie should return default value for key.
    TEST(trie.get("abc", 3) == no_match);

    // Empty trie should not match empty key.
    TEST(trie.get("", 0) == no_match);

    trie.insert("ab", 2, 1);

    // Trie should return default value for non-existent key.
    TEST(trie.get("abc", 3) == no_match);

    // Trie should match existing keys.
    TEST(trie.get("ab", 2) == 1);
}
END_TEST

START_TEST(DefaultTrie_InsertTest)
{
    DefaultTrie<char, int> trie(no_match);

    // After inserting a key, the trie should match it.
    trie.insert("ab", 2, 1);
    TEST(trie.get("ab", 2) == 1);

    // Shared prefixes should not affect the trie.
    trie.insert("abc", 3, 2);
    trie.insert("abd", 3, 3);

    TEST(trie.get("ab", 2) == 1);
    TEST(trie.get("abc", 3) == 2);
    TEST(trie.get("abd", 3) == 3);
}
END_TEST

START_TEST(DefaultTrie_RemoveTest)
{
    DefaultTrie<char, int> trie(no_match);

    trie.insert("a", 1, 1);
    trie.insert("ab", 2, 2);
    trie.insert("abc", 3, 3);

    // Removing a key works.
    trie.remove("ab", 2);
    TEST(trie.get("ab", 2) == no_match);

    // Neither the children or parents are removed.
    TEST(trie.get("abc", 3) == 3);
    TEST(trie.get("a", 1) == 1);
}
END_TEST

START_TEST(DefaultTrie_UpdateDefaultReturn)
{
    DefaultTrie<char, int> trie(no_match);

    // The default return value can be updated.
    ASSERT(trie.get("abc", 3) != 1);
    trie.update_default_return(1);
    TEST(trie.get("abc", 3) == 1);
}
END_TEST

END_SUITE
