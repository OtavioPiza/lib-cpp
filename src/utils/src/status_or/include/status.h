#ifndef LIBCC_STATUS_H
#define LIBCC_STATUS_H

namespace ostp::libcc::utils
{
    /// Represents the status of an operation.
    enum class Status
    {
        /// The operation was successful.
        OK,

        /// The operation failed.
        ERROR
    };
}

#endif
