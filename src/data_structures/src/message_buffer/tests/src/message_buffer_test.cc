#include "message_buffer.h"

#include <chrono>
#include <sstream>
#include <string>
#include <thread>
#include <memory>

#include "logger.h"
#include "status.h"
#include "testing.h"

using ostp::libcc::data_structures::MessageBuffer;
using ostp::libcc::utils::log_error;
using ostp::libcc::utils::Status;
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

    auto size_res = queue.size();
    TEST(size_res.result == 0);
    TEST(size_res.status == Status::OK);
}
END_TEST

START_TEST(PushUnblocksPop) {
    MessageBuffer<string> queue;

    // Create a thread to pop.
    auto t1 = thread([&]() {
        auto pop_res = queue.pop();
        TEST(pop_res.result == message1);
        TEST(pop_res.status == Status::OK);
    });

    // Push message.
    queue.push(string(message1));
    t1.join();
}
END_TEST

START_TEST(MessagesAreDeliveredInOrder) {
    MessageBuffer<string> queue;

    // Create a thread to pop.
    auto t1 = thread([&]() {
        TEST(queue.pop().result == message1);
        TEST(queue.pop().result == message2);
    });

    // Push message.
    queue.push(string(message1));
    queue.push(string(message2));
    t1.join();
}
END_TEST

START_TEST(PopWithTimeoutCanUnblockNormally) {
    MessageBuffer<string> queue;

    // Create a thread to pop.
    auto t1 = thread([&]() {
        auto pop_res = queue.pop(10000000);
        TEST(pop_res.result == message1);
        TEST(pop_res.status == Status::OK);
    });

    // Push message.
    queue.push(string(message1));
    t1.join();
}
END_TEST

START_TEST(PopWithTimeoutUnblocksAfterTimeoutWithTimeoutStatus) {
    MessageBuffer<string> queue;
    auto pop_res = queue.pop(10);
    TEST(pop_res.status == Status::TIMEOUT);
    TEST(queue.is_closed() == true);
}
END_TEST

START_TEST(CloseUnblocksPop) {
    MessageBuffer<string> queue;

    // Create a thread to pop.
    auto t1 = thread([&]() {
        auto pop_res = queue.pop();
        TEST(pop_res.status == Status::EMPTY);
    });

    // Close the queue.
    queue.close();
    t1.join();
}
END_TEST

START_TEST(MessagesInTheBufferAreRetrievableAfterClose) {
    MessageBuffer<string> queue;
    queue.push(string(message1));
    queue.push(string(message2));

    // Close the queue.
    queue.close();

    // Pop the messages.
    auto pop1_res = queue.pop();
    TEST(pop1_res.result == message1);
    TEST(pop1_res.status == Status::CLOSED);

    auto pop2_res = queue.pop();
    TEST(pop2_res.result == message2);
    TEST(pop2_res.status == Status::CLOSED);

    // The queue should be closed and empty.
    TEST(queue.is_closed());
    TEST(queue.empty());
    TEST(queue.pop().status == Status::EMPTY);

}
END_TEST

END_SUITE
