#include <string>
#include "../include/logger.h"
#include "colors.h"
#include "streams.h"

// See logger.h for documentation.
void ostp::libcc::utils::log_info(const std::string &msg, const std::string &sender)
{
    fprintf(INFO_STREAM,
            NORMAL
            "[%s] INFO: %s"
            NORMAL,
            sender.c_str(), msg.c_str());
}

// See logger.h for documentation.
void ostp::libcc::utils::log_success(const std::string &msg, const std::string &sender)
{
    fprintf(INFO_STREAM,
            GREEN
            "[%s] SUCCESS: %s"
            NORMAL,
            sender.c_str(), msg.c_str());
}

// See logger.h for documentation.
void ostp::libcc::utils::log_warn(const std::string &msg, const std::string &sender)
{
    fprintf(INFO_STREAM,
            YELLOW
            "[%s] WARN: %s"
            NORMAL,
            sender.c_str(), msg.c_str());
}

// See logger.h for documentation.
void ostp::libcc::utils::log_error(const std::string &msg, const std::string &sender)
{
    fprintf(ERROR_STREAM,
            RED
            "[%s] ERROR: %s"
            NORMAL,
            sender.c_str(), msg.c_str());
}
