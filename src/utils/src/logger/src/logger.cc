#include <string>

#include "logger.h"
#include "colors.h"
#include "streams.h"

namespace ostp::libcc::utils
{
// See logger.h for documentation.
void log_info(const char *msg, const char *sender)
{
    fprintf(INFO_STREAM, NORMAL "[%s] INFO: %s" NORMAL, sender, msg);
}

// See logger.h for documentation.
void log_success(const char *msg, const char *sender)
{
    fprintf(INFO_STREAM, GREEN "[%s] SUCCESS: %s" NORMAL, sender, msg);
}

// See logger.h for documentation.
void log_warn(const char *msg, const char *sender)
{
    fprintf(INFO_STREAM, YELLOW "[%s] WARN: %s" NORMAL, sender, msg);
}

// See logger.h for documentation.
void log_error(const char *msg, const char *sender)
{
    fprintf(ERROR_STREAM, RED "[%s] ERROR: %s" NORMAL, sender, msg);
}

}   // namespace ostp::libcc::util
