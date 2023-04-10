#ifndef LIBCC_TESTING_H
#define LIBCC_TESTING_H

#include <cstring>

#include "logger.h"

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define START_SUITE(name)                      \
    int main()                                 \
    {                                          \
        const std::string _suite_name = #name; \
        int _tests_failed = 0;                 \
        int _tests_passed = 0;

#define START_TEST(name) \
    [&_tests_failed, &_tests_passed]() {            \
        const std::string _test_name = #name;       \
        bool _failed = false;

#define ASSERT(expr)                                                                    \
    if (!(expr))                                                                        \
    {                                                                                   \
        ostp::libcc::utils::log_error("Assertion '" #expr "' Failed!\n", __FILENAME__); \
        _tests_failed++;                                                                \
        return;                                                                         \
    }

#define TEST(expr)                                                                       \
    if (!(expr))                                                                         \
    {                                                                                    \
        _failed = true;                                                                  \
        ostp::libcc::utils::log_error("Expression '" #expr "' Failed!\n", __FILENAME__); \
    }

#define END_TEST                                                                              \
    if (_failed)                                                                              \
    {                                                                                         \
        ostp::libcc::utils::log_error("Test '" + _test_name + "' failed!\n", __FILENAME__);   \
        _tests_failed++;                                                                      \
    }                                                                                         \
    else                                                                                      \
    {                                                                                         \
        ostp::libcc::utils::log_ok("Test '" + _test_name + "' passed!\n", __FILENAME__); \
        _tests_passed++;                                                                      \
    }                                                                                         \
    }                                                                                         \
    ();

#define END_SUITE                                                                               \
    if (_tests_failed)                                                                          \
    {                                                                                           \
        ostp::libcc::utils::log_error("Suite '" + _suite_name + "' failed!\n", __FILENAME__);   \
        return 1;                                                                               \
    }                                                                                           \
    else                                                                                        \
    {                                                                                           \
        ostp::libcc::utils::log_ok("Suite '" + _suite_name + "' passed!\n", __FILENAME__); \
        return 0;                                                                               \
    }                                                                                           \
    }

#endif
