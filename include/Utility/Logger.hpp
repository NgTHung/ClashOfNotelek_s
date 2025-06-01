#pragma once
#include <chrono>
#include <format>

enum class LogLevel
{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class Logger
{
private:
    Logger() = delete;
    ~Logger() = delete;
    static LogLevel CurrentLogLevel;
    static const std::string RESET_COLOR;
    static const std::string DEBUG_COLOR;
    static const std::string INFO_COLOR;
    static const std::string WARNING_COLOR;
    static const std::string ERROR_COLOR;
    static const std::string CRITICAL_COLOR;
    static const std::string TIMESTAMP_COLOR;
    static const std::string FILE_LINE_COLOR;
    static std::string GetTimestamp();
    static std::string LogLevelToString(LogLevel level);
    static std::string GetColor(LogLevel level);

public:
    static void SetLogLevel(const LogLevel NewLevel);
    static LogLevel GetLogLevel();
    static void Log(LogLevel level, const char *file, int line, const std::string &message);
};

#define LOG_MSG(level, fmt_str, ...)                                                                                     \
    do                                                                                                                   \
    {                                                                                                                    \
        if (level >= Logger::GetLogLevel())                                                                              \
        {                                                                                                                \
            try                                                                                                          \
            {                                                                                                            \
                std::string formatted_msg = std::format(fmt_str, ##__VA_ARGS__);                                         \
                Logger::Log(level, __FILE__, __LINE__, formatted_msg);                                                   \
            }                                                                                                            \
            catch (const std::format_error &e)                                                                           \
            {                                                                                                            \
                /* Handle formatting error, e.g., log a fallback message */                                              \
                std::string error_msg = std::string("Formatting error: ") + e.what() + " | Original format: " + fmt_str; \
                Logger::Log(LogLevel::ERROR, __FILE__, __LINE__, error_msg);                                             \
            }                                                                                                            \
        }                                                                                                                \
    } while (0)

#define LOG_DEBUG(fmt_str, ...) LOG_MSG(LogLevel::DEBUG, fmt_str, ##__VA_ARGS__)
#define LOG_INFO(fmt_str, ...) LOG_MSG(LogLevel::INFO, fmt_str, ##__VA_ARGS__)
#define LOG_WARNING(fmt_str, ...) LOG_MSG(LogLevel::WARNING, fmt_str, ##__VA_ARGS__)
#define LOG_ERROR(fmt_str, ...) LOG_MSG(LogLevel::ERROR, fmt_str, ##__VA_ARGS__)
#define LOG_CRITICAL(fmt_str, ...) LOG_MSG(LogLevel::CRITICAL, fmt_str, ##__VA_ARGS__)