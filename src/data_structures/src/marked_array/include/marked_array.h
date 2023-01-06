#ifndef MARKED_ARRAY_H
#define MARKED_ARRAY_H

#include <vector>

#include "marked_array_entry.h"

namespace ostp::libcc::data_structures
{
    /// Memory marked array for constant time initialization and access.
    template <typename K>
    class MarkedArray
    {
    public:
        /// Constructs a new memory marked array with the specified size.
        ///
        /// Arguments:
        ///     size: the size of the array.
        ///     default_return: value returned for uninitialized positions.
        MarkedArray(int size, K default_return)
            : _size(size), _markings(new int[size]), _entries(new MarkedArrayEntry<K>[size]),
              _default_return(default_return)
        {
            _initialized_count = 0;
        }

        /// Destructor.
        ~MarkedArray()
        {
            delete[] _markings;
            delete[] _entries;
        }

        /// Checks whether an index at the array is initialized.
        ///
        /// Arguments:
        ///     index: index in the array.
        ///
        /// Returns:
        ///     whether the index in the array is initialized.
        bool is_initialzed(int index)
        {
            // Check validity of the index.
            if (index < 0 || index >= _size)
            {
                throw std::runtime_error("Index out of bounds");
            }

            // Check if the specified index is initialized.
            return (_entries[index].mark >= 0 &&                 // Marking is greater than 0.
                    _entries[index].mark < _initialized_count && // Marking is less the initialized.
                    _markings[_entries[index].mark] == index);   // Marking is valid.
        }

        /// Checks whether an index at the array is uninitialized.
        ///
        /// Arguments:
        ///     index: index in the array.
        ///
        /// Returns:
        ///     whether the index in the array is uninitialized.
        bool is_uninitialized(int index)
        {
            return !is_initialzed(index);
        }

        /// Returns the number of initialized elements.
        ///
        /// Returns:
        ///     the number of initialized elements.
        int initialized_count()
        {
            return _initialized_count;
        }

        /// Returns the size of the array.
        ///
        /// Returns:
        ///     the size of the array.
        int size()
        {
            return _size;
        }

        /// Returns the value stored in the specified position.
        ///
        /// Arguments:
        ///     index of the items in the array.
        ///
        /// Returns:
        ///     the value of the element.
        const K get(int index)
        {
            // If the value is initialized return it; otherwise return the default value.
            if (is_initialzed(index))
            {
                return _entries[index].value;
            }
            return _default_return;
        }

        /// Inserts or updates a value.
        ///
        /// Arguments:
        ///     index: index of the element.
        ///     value: value of the element.
        void insert(int index, K value)
        {
            // If the value is initialized update; otherwise create a new one.
            if (is_initialzed(index))
            {
                _entries[index].value = value;
                return;
            }

            // Create new marking.
            _entries[index] = MarkedArrayEntry<K>{_initialized_count, value};
            _markings[_initialized_count++] = index;
        }

    private:
        const int _size;               // Size of the array.
        const K _default_return;       // Default value returned for uninitialized positions.
        int _initialized_count;        // Number of initialized elements.
        int *_markings;                // Array of markings.
        MarkedArrayEntry<K> *_entries; // Array of entries.
    };
} // namespace ostp::libcc::data_structures.

#endif
