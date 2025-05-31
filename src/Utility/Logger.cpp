#include "Utility/Logger.hpp"
#include <iostream>

LogLevel Logger::CurrentLogLevel = LogLevel::DEBUG;

const std::string Logger::RESET_COLOR = "\033[0m";
const std::string Logger::DEBUG_COLOR = "\033[36m";
const std::string Logger::INFO_COLOR = "\033[32m";
const std::string Logger::WARNING_COLOR = "\033[33m";
const std::string Logger::ERROR_COLOR = "\033[31m";
const std::string Logger::CRITICAL_COLOR = "\033[1;31m";
const std::string Logger::TIMESTAMP_COLOR = "\033[90m";
const std::string Logger::FILE_LINE_COLOR = "\033[35m";

LogLevel Logger::GetLogLevel()
{
    return CurrentLogLevel;
}

void Logger::SetLogLevel(const LogLevel NewLevel)
{
    CurrentLogLevel = NewLevel;
}

std::string Logger::GetTimestamp()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&in_time_t);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
    return std::string(buffer);
}

std::string Logger::LogLevelToString(LogLevel level)
{
    switch (level)
    {
    case LogLevel::DEBUG:
        return "DEBUG";
    case LogLevel::INFO:
        return "INFO";
    case LogLevel::WARNING:
        return "WARNING";
    case LogLevel::ERROR:
        return "ERROR";
    case LogLevel::CRITICAL:
        return "CRITICAL";
    default:
        return "UNKNOWN";
    }
}

std::string Logger::GetColor(LogLevel level)
{
    switch (level)
    {
    case LogLevel::DEBUG:
        return DEBUG_COLOR;
    case LogLevel::INFO:
        return INFO_COLOR;
    case LogLevel::WARNING:
        return WARNING_COLOR;
    case LogLevel::ERROR:
        return ERROR_COLOR;
    case LogLevel::CRITICAL:
        return CRITICAL_COLOR;
    default:
        return RESET_COLOR;
    }
}

void Logger::Log(LogLevel level, const char *file, int line, const std::string &message)
{
    if (level < CurrentLogLevel)
    {
        return;
    }

    std::ostream &out_stream = (level >= LogLevel::ERROR) ? std::cerr : std::cout;

    out_stream << GetColor(level);
    out_stream << "[" << TIMESTAMP_COLOR << GetTimestamp() << RESET_COLOR << GetColor(level) << "]";
    out_stream << "[" << std::setw(8) << std::right << LogLevelToString(level) << "]";

    if (file && line > 0)
    {
        const char *filename_only = file;
        const char *p = file;
        while (*p)
        {
            if (*p == '/' || *p == '\\')
            {
                filename_only = p + 1;
            }
            p++;
        }
        out_stream << "[" << FILE_LINE_COLOR << filename_only << ":" << line << RESET_COLOR << GetColor(level) << "]";
    }

    out_stream << " " << message;
    out_stream << RESET_COLOR;
    out_stream << std::endl;
}