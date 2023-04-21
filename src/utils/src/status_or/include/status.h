#ifndef LIBCC_STATUS_H
#define LIBCC_STATUS_H

namespace ostp::libcc::utils {

/// Represents the status of an operation.
enum class Status {
    /// Cancellation status.
    CANCELLED,

    /// Closed status.
    CLOSED,

    /// Empty status.
    EMPTY,

    /// Error status.
    ERROR,

    /// Informational status.
    INFO,

    /// OK status.
    OK,

    /// Time out status.
    TIMEOUT,

    /// Warning status.
    WARNING
};

}  // namespace ostp::libcc::utils

#endif
