#ifndef LIBCC_STATUS_H
#define LIBCC_STATUS_H

namespace ostp::libcc::utils
{
    /// Represents the status of an operation.
    enum class Status
    {
        /// The operation was successful.
        SUCCESS,

        /// The operation had a warning.
        WARNING,

        /// The operation failed.
        ERROR,

        /// The operation was cancelled.
        CANCELLED,

        /// The operation had an unknown status.
        UNKNOWN
    };
}

#endif
