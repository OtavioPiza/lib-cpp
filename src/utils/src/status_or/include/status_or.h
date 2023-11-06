#ifndef LIBCC_STATUS_OR_H
#define LIBCC_STATUS_OR_H

#include "status.h"

namespace ostp::libcc::utils {
/// Represents the status of an operation and the result of that operation.
template <typename T>
struct StatusOr {
    /// The status of the operation.
    const Status status;

    /// The status message of the operation.
    const char *status_message;

    /// The result of the operation.
    T result;

    /// Constructs a StatusOr with the given status and result.
    ///
    /// Arguments:
    ///     status: The status of the operation.
    ///     result: The result of the operation.
    StatusOr(const Status status, const char *status_message, T &&result)
        : status(status), result(std::move(result)), status_message(status_message) {}

    // Methods to check the status of the operation.

    /// Returns true if the operation was successful.
    bool ok() const { return status == Status::OK; }

    /// Returns true if the operation failed.
    bool failed() const { return status != Status::OK; }
};

/// Specialization of StatusOr for void.
template <>
struct StatusOr<void> {
    /// The status of the operation.
    const Status status;

    /// The status message of the operation.
    const char *status_message;

    /// Constructs a StatusOr with the given status.
    ///
    /// Arguments:
    ///     status: The status of the operation.
    StatusOr(const Status status, const char *status_message)
        : status(status), status_message(status_message) {}

    // Methods to check the status of the operation.

    /// Returns true if the operation was successful.
    bool ok() const { return status == Status::OK; }

    /// Returns true if the operation failed.
    bool failed() const { return status != Status::OK; }
};
}  // namespace ostp::libcc::utils

#endif
