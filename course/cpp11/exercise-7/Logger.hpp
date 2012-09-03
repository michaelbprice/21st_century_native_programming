#ifndef INCL_LOGGER_HPP__
#define INCL_LOGGER_HPP__

#include <iostream>
#include <utility>

namespace Go {

enum class LogLevel : unsigned char
{
    kNone = 0,
    kLow = 1,
    kMedium = 2,
    kHigh = 3,
    kFirehose = 4
};

class Logger
{
 private:
    LogLevel m_level;

 public:
    Logger (LogLevel level)
      : m_level(level)
    { }

    template <typename T>
    void log (LogLevel level, T && t)
    {    
        if (level <= m_level)
        {
            std::cout << "LOG(" << static_cast<unsigned short>(level) << "): ";
            doLog(level, std::forward<T>(t));
        }
    }

 private:

    template <typename T>
    void doLog (LogLevel level, T && t)
    {
        std::cout << t << std::endl; 
    }
};

} // namespace Go

extern Go::Logger gLogger;

#endif /* end of include guard: INCL_LOGGER_HPP__ */
