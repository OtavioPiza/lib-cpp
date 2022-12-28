#ifndef LOGGER_H
#define LOGGER_H

#include <string>

namespace ostp::libcc::utils
{
    /// Logs a message with the INFO level.
    ///
    /// Args:
    ///     msg: The message to log.
    ///     sender: The name of the sender of the message.
    void log_info(const std::string &msg, const std::string &sender);

    /// Logs a message with the SUCCESS level.
    ///
    /// Args:
    ///     msg: The message to log.
    ///     sender: The name of the sender of the message.
    void log_success(const std::string &msg, const std::string &sender);

    /// Logs a message with the WARN level.
    ///
    /// Args:
    ///     msg: The message to log.
    ///     sender: The name of the sender of the message.
    void log_warn(const std::string &msg, const std::string &sender);

    /// Logs a message with the ERROR level.
    ///
    /// Args:
    ///     msg: The message to log.
    ///     sender: The name of the sender of the message.
    void log_error(const std::string &msg, const std::string &sender);

}   // namespace ostp::libcc::util

#endif