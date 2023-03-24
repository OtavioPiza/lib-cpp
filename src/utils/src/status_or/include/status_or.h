#ifndef LIBCC_STATUS_OR_H
#define LIBCC_STATUS_OR_H

#include "status.h"

namespace ostp::libcc::utils
{
    /// Represents the status of an operation and the result of that operation.
    template <typename T>
    struct StatusOr
    {
        /// The status of the operation.
        const Status status;

        /// The status message of the operation.
        const char *status_message;

        /// The result of the operation.
        const T result;

        /// Constructs a StatusOr with the given status and result.
        ///
        /// Arguments:
        ///     status: The status of the operation.
        ///     result: The result of the operation.
        StatusOr(const Status status, const char *status_message, const T result)
            : status(status), result(result), status_message(status_message) {}

        // Methods to check the status of the operation.

        /// Returns true if the operation was successful.
        bool ok() const { return status == Status::OK; }

        /// Returns true if the operation failed.
        bool failed() const { return status != Status::OK; }
    };
}

#endif
