#include "message_queue.h"

#include <sstream>
#include <string>

#include "logger.h"
#include "testing.h"

using ostp::libcc::data_structures::MessageQueue;
using ostp::libcc::utils::log_error;
using std::stringstream;

const int no_match = -1;

START_SUITE(MessageQueue_Tests)

START_TEST(EmptyStringShouldHaveNoMatch) {
    MessageQueue queue;

    // The queue should be open and empty.
    TEST(!queue.is_closed());
    TEST(queue.empty());
}
END_TEST

END_SUITE
