#ifndef MARKED_ARRAY_ENTRY_H
#define MARKED_ARRAY_ENTRY_H

namespace ostp::libcc::data_structures
{
    /// Represents an entry in the MarkedArray data structure
    template <typename K>
    struct MarkedArrayEntry
    {
        /// Location of the memory mark that points to this entry.
        int mark;

        /// Value stored in that location.
        K value;
    };

} // namespace ostp::libcc::data_structures;

#endif
