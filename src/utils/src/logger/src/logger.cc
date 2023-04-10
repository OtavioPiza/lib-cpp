#include <string>

#include "logger.h"
#include "colors.h"
#include "streams.h"

namespace ostp::libcc::utils
{
    // See logger.h for documentation.
    void log_info(const std::string &msg, const std::string &sender)
    {
        fprintf(INFO_STREAM, NORMAL "[%s] %s\n" NORMAL, sender.c_str(), msg.c_str());
    }

    // See logger.h for documentation.
    void log_ok(const std::string &msg, const std::string &sender)
    {
        fprintf(INFO_STREAM, GREEN "[%s] %s\n" NORMAL, sender.c_str(), msg.c_str());
    }

    // See logger.h for documentation.
    void log_warn(const std::string &msg, const std::string &sender)
    {
        fprintf(WARN_STREAM, YELLOW "[%s] %s\n" NORMAL, sender.c_str(), msg.c_str());
    }

    // See logger.h for documentation.
    void log_error(const std::string &msg, const std::string &sender)
    {
        fprintf(ERROR_STREAM, RED "[%s] %s\n" NORMAL, sender.c_str(), msg.c_str());
    }

} // namespace ostp::libcc::util
