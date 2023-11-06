#include "message_buffer.h"

#include <chrono>
#include <memory>
#include <sstream>
#include <string>
#include <thread>

#include "absl/status/status.h"
#include "logger.h"
#include "testing.h"

using ostp::libcc::data_structures::MessageBuffer;
using ostp::libcc::utils::log_error;
using std::stringstream;
using std::thread;

const string message1 = "abc";
const string message2 = "def";

START_SUITE(MessageBuffer_Tests)

START_TEST(ConstructsEmptyQueue) {
    MessageBuffer<string> queue;

    // The queue should be open and empty.
    TEST(!queue.is_closed());
    TEST(queue.empty());

    auto [status, size] = queue.size();
    TEST(size == 0);
    TEST(status == absl::OkStatus());
}
END_TEST

START_TEST(PushUnblocksPop) {
    MessageBuffer<string> queue;

    // Create a thread to pop.
    auto t1 = thread([&]() {
        auto [status, res] = queue.pop();
        TEST(status == absl::OkStatus());
        TEST(res == message1);
    });

    // Push message.
    TEST(queue.push(string(message1)) == absl::OkStatus());
    t1.join();
}
END_TEST

START_TEST(MessagesAreDeliveredInOrder) {
    MessageBuffer<string> queue;

    // Create a thread to pop.
    auto t1 = thread([&]() {
        auto [status1, res1] = queue.pop();
        TEST(status1 == absl::OkStatus());
        TEST(res1 == message1);

        auto [status2, res2] = queue.pop();
        TEST(status2 == absl::OkStatus());
        TEST(res2 == message2);
    });

    // Push message.
    TEST(queue.push(string(message1)) == absl::OkStatus());
    TEST(queue.push(string(message2)) == absl::OkStatus());
    t1.join();
}
END_TEST

START_TEST(PopWithTimeoutCanUnblockNormally) {
    MessageBuffer<string> queue;

    // Create a thread to pop.
    auto t1 = thread([&]() {
        auto [status, res] = queue.pop(10000000);
        TEST(status == absl::OkStatus());
        TEST(res == message1);
    });

    // Push message.
    TEST(queue.push(string(message1)) == absl::OkStatus());
    t1.join();
}
END_TEST

START_TEST(PopWithTimeoutUnblocksAfterTimeoutWithTimeoutStatus) {
    MessageBuffer<string> queue;
    auto [status, res] = queue.pop(10);
    TEST(status.code() == absl::StatusCode::kDeadlineExceeded);
}
END_TEST

START_TEST(CloseUnblocksPop) {
    MessageBuffer<string> queue;

    // Create a thread to pop.
    auto t1 = thread([&]() {
        auto [status, res] = queue.pop();
        TEST(status.code() == absl::StatusCode::kCancelled);
        TEST(res == "");
    });

    // Close the queue.
    queue.close();
    t1.join();
}
END_TEST

START_TEST(MessagesInTheBufferAreRetrievableAfterClose) {
    MessageBuffer<string> queue;
    TEST(queue.push(string(message1)) == absl::OkStatus());
    TEST(queue.push(string(message2)) == absl::OkStatus());

    // Close the queue.
    queue.close();

    // Pop the messages.
    auto [pop1_status, pop1_res] = queue.pop();
    TEST(pop1_status == absl::OkStatus());
    TEST(pop1_res == message1);

    auto [pop2_status, pop2_res] = queue.pop();
    TEST(pop2_status == absl::OkStatus());

    // The queue should be closed and empty.
    TEST(queue.is_closed());
    TEST(queue.empty());

    auto [size_status, size] = queue.size();
    TEST(size == 0);

    TEST(queue.pop().first.code() == absl::StatusCode::kCancelled);
}
END_TEST

END_SUITE
