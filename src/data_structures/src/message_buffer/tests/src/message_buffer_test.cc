#include "message_buffer.h"

#include <chrono>
#include <sstream>
#include <string>
#include <thread>

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
    MessageBuffer queue;

    // The queue should be open and empty.
    TEST(!queue.is_closed());
    TEST(queue.empty());

    auto size_res = queue.size();
    TEST(size_res.result == 0);
    TEST(size_res.status == Status::OK);
}
END_TEST

START_TEST(PushUnblocksPop) {
    MessageBuffer queue;

    // Create a thread to pop.
    auto t1 = thread([&]() {
        auto pop_res = queue.pop();
        TEST(pop_res.result == message1);
        TEST(pop_res.status == Status::OK);
    });

    // Push message.
    queue.push(message1);
    t1.join();
}
END_TEST

START_TEST(MessagesAreDeliveredInOrder) {
    MessageBuffer queue;

    // Create a thread to pop.
    auto t1 = thread([&]() {
        TEST(queue.pop().result == message1);
        TEST(queue.pop().result == message2);
    });

    // Push message.
    queue.push(message1);
    queue.push(message2);
    t1.join();
}
END_TEST

START_TEST(PopWithTimeoutCanUnblockNormally) {
    MessageBuffer queue;

    // Create a thread to pop.
    auto t1 = thread([&]() {
        auto pop_res = queue.pop(10000000);
        TEST(pop_res.result == message1);
        TEST(pop_res.status == Status::OK);
    });

    // Push message.
    queue.push(message1);
    t1.join();
}
END_TEST

START_TEST(PopWithTimeoutUnblocksAfterTimeoutWithTimeoutStatus) {
    MessageBuffer queue;
    auto pop_res = queue.pop(10);
    TEST(pop_res.status == Status::TIMEOUT);
    TEST(queue.is_closed() == true);
}
END_TEST

START_TEST(CloseUnblocksPop) {
    MessageBuffer queue;

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
    MessageBuffer queue;
    queue.push(message1);
    queue.push(message2);

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
