#ifndef LOGGER_H
#define LOGGER_H

namespace ostp::libcc::utils
{
    /// Logs a message with the INFO level.
    ///
    /// Args:
    ///     msg: The message to log.
    ///     sender: The name of the sender of the message.
    void log_info(const char *, const char *);

    /// Logs a message with the SUCCESS level.
    ///
    /// Args:
    ///     msg: The message to log.
    ///     sender: The name of the sender of the message.
    void log_success(const char *, const char *);

    /// Logs a message with the WARN level.
    ///
    /// Args:
    ///     msg: The message to log.
    ///     sender: The name of the sender of the message.
    void log_warn(const char *, const char *);

    /// Logs a message with the ERROR level.
    ///
    /// Args:
    ///     msg: The message to log.
    ///     sender: The name of the sender of the message.
    void log_error(const char *, const char *);

}   // namespace ostp::libcc::util

#endif