#include "message_queue.h"

#include <sstream>
#include <string>

#include "logger.h"
#include "testing.h"

using ostp::libcc::data_structures::DefaultTrie;
using ostp::libcc::utils::log_error;
using std::stringstream;

const int no_match = -1;

START_SUITE(MessageQueue_Tests)

START_TEST(EmptyStringShouldHaveNoMatch) {
}
END_TEST

// START_TEST(DefaultTrie_ContainsTest) {
//     DefaultTrie<char, int> trie(no_match);

//     // The trie should not contain any keys.
//     TEST(!trie.contains("abc", 3));

//     trie.insert("abc", 3, 1);

//     // The trie should contain the inserted key.
//     TEST(trie.contains("abc", 3));
// }
// END_TEST

END_SUITE
