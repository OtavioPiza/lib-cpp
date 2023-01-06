#include <sstream>
#include <string>

#include "marked_array.h"
#include "logger.h"
#include "testing.h"

using ostp::libcc::data_structures::MarkedArray;
using ostp::libcc::utils::log_error;
using std::stringstream;

const int default_return = 0;  // Default value returned for uninitialized positions.
const int insertion_value = 1; // Value inserted into the array.
const int update_value = 2;    // Value updated in the array.
const int size = 10;           // Size of the array.

START_SUITE(MarkedArray_Tests)

START_TEST(MarkedArray_Constructor)
{
    MarkedArray<int> array(size, 0);

    // Check size of the array.
    ASSERT(array.size() == size);

    // Check that at first no values are initialized.
    TEST(array.initialized_count() == 0);
    for (int i = 0; i < size; i++)
    {
        TEST(array.is_uninitialized(i));
    }

    // Check that the default value is returned for uninitialized positions.
    for (int i = 0; i < size; i++)
    {
        TEST(array.get(i) == default_return);
    }
}
END_TEST

START_TEST(MarkedArray_Insertion)
{
    MarkedArray<int> array(size, 0);
    const int insertion_i = size / 2;

    // Insert values into the array.
    int initialized_count = array.initialized_count();
    TEST(array.is_uninitialized(insertion_i));
    array.insert(insertion_i, insertion_value);
    TEST(array.initialized_count() == initialized_count + 1);
    TEST(array.is_initialzed(insertion_i));
    TEST(array.get(insertion_i) == insertion_value);

    // Update values in the array.
    initialized_count = array.initialized_count();
    TEST(array.is_initialzed(insertion_i));
    array.insert(insertion_i, update_value);
    TEST(array.initialized_count() == initialized_count);
    TEST(array.is_initialzed(insertion_i));
    TEST(array.get(insertion_i) == update_value);
}
END_TEST

START_TEST(MarkedArray_Get)
{
    MarkedArray<int> array(size, 0);

    // Check that the default value is returned for uninitialized positions.
    for (int i = 0; i < size; i++)
    {
        TEST(array.get(i) == default_return);
        array.insert(i, insertion_value);
    }

    // Check that the specified value is returned for initialized positions.
    for (int i = 0; i < size; i++)
    {
        TEST(array.get(i) == insertion_value);
        array.insert(i, update_value);
    }

    // Check that the updated value is returned for updated positions.
    for (int i = 0; i < size; i++)
    {
        TEST(array.get(i) == update_value);
    }
}
END_TEST

END_SUITE
