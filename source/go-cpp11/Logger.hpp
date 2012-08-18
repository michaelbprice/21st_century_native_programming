#ifndef __LOGGER_HPP
#define __LOGGER_HPP

#include <ostream>
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
    LogLevel m_level = LogLevel::kNone;

 public:
    Logger (LogLevel level)
      : m_level(level)
    { }

    template <typename ... Args>
    std::ostream & log (LogLevel level, std::ostream & out, Args && ...args)
    {    
        if (level <= m_level)
        {
            out << "LOG(" << static_cast<unsigned short>(level) << "): ";
            return doLog(level, out, std::forward<Args>(args)...);
        }

        return out;
    }

 private:

    template <typename T, typename ... Args>
    std::ostream & doLog (LogLevel level, std::ostream & out, T && t, Args && ...args)
    {    
        return doLog(level, out << t, std::forward<Args>(args)...);
    }

    template <typename T>
    std::ostream & doLog (LogLevel level, std::ostream & out, T && t)
    {
       return out << t << std::endl; 
    }
};

} // namespace Go

#ifdef MAIN_CPP
Go::Logger gLogger {Go::LogLevel::kHigh};
#else
extern Go::Logger gLogger;
#endif

namespace Go {

struct FunctionLogger
{
    FunctionLogger (LogLevel level, std::ostream & out, const char * methodName)
      : m_level{level}
      , m_out{out}
      , m_name{methodName}
    {
        gLogger.log(m_level, m_out, std::string(kIndention * nestingLevel, '='), ">> ", m_name);
        ++nestingLevel;
    }

    ~FunctionLogger ()
    {
        --nestingLevel;
        gLogger.log(m_level, m_out, "<<", std::string(kIndention * nestingLevel, '='), " ", m_name);
    }

    LogLevel m_level = LogLevel::kHigh;
    std::ostream & m_out;
    const char * m_name = nullptr;

    static const unsigned short kIndention = 2;
    static unsigned short nestingLevel;
};

#ifdef MAIN_CPP
unsigned short FunctionLogger::nestingLevel = 1;
#endif

#define LOG_FUNCTION(stream, fnname) FunctionLogger _fnLogger {LogLevel::kHigh, stream, fnname};
#define LOG_BUSY_FUNCTION(stream, fnname) FunctionLogger _fnLogger {LogLevel::kFirehose, stream, fnname};

} // namespace Go

#endif // __LOGGER_HPP
