#ifndef INCL_LOGGER_HPP__
#define INCL_LOGGER_HPP__

#include <iosfwd>
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

class Logger final
{
 private:
    LogLevel m_level;

 public:
    Logger (LogLevel level)
      : m_level(level)
    { }

    //template <typename ... Args>
    //std::wostream & log (LogLevel level, std::wostream & out, Args && ...args)
    template <typename T1>
    std::wostream & log (LogLevel level, std::wostream & out, T1 && t1)
    {    
        if (level <= m_level)
        {
            out << L"LOG(" << static_cast<unsigned short>(level) << L"): ";
            return out << t1 << std::endl; 
        }

        return out;
    }

    template <typename T1, typename T2>
    std::wostream & log (LogLevel level, std::wostream & out, T1 && t1, T2 && t2)
    {    
        if (level <= m_level)
        {
            out << "LOG(" << static_cast<unsigned short>(level) << "): ";
            return out << t1 << t2 << std::endl; 
        }

        return out;
    }

    template <typename T1, typename T2, typename T3>
    std::wostream & log (LogLevel level, std::wostream & out, T1 && t1, T2 && t2, T3 && t3)
    {    
        if (level <= m_level)
        {
            out << L"LOG(" << static_cast<unsigned short>(level) << L"): ";
            return out << t1 << t2 << t3 << std::endl; 
        }

        return out;
    }

    template <typename T1, typename T2, typename T3, typename T4>
    std::wostream & log (LogLevel level, std::wostream & out, T1 && t1, T2 && t2, T3 && t3, T4 && t4)
    {    
        if (level <= m_level)
        {
            out << L"LOG(" << static_cast<unsigned short>(level) << L"): ";
            return out << t1 << t2 << t3 << t4 << std::endl; 
        }

        return out;
    }

    template <typename T1, typename T2, typename T3, typename T4, typename T5>
    std::wostream & log (LogLevel level, std::wostream & out, T1 && t1, T2 && t2, T3 && t3, T4 && t4, T5 && t5)
    {    
        if (level <= m_level)
        {
            out << L"LOG(" << static_cast<unsigned short>(level) << L"): ";
            return out << t1 << t2 << t3 << t4 << t5 << std::endl; 
        }

        return out;
    }

 private:

    //template <typename T, typename ... Args>
    //std::wostream & doLog (LogLevel level, std::wostream & out, T && t, Args && ...args)
    //{    
    //    return doLog(level, out << t, std::forward<Args>(args)...);
    //}

    //template <typename T>
    //std::wostream & doLog (LogLevel level, std::wostream & out, T && t)
    //{
    //}
};

} // namespace Go

#ifdef MAIN_CPP
Go::Logger gLogger(Go::LogLevel::kHigh);
#else
extern Go::Logger gLogger;
#endif

namespace Go {

struct FunctionLogger final
{
    FunctionLogger (LogLevel level, std::wostream & out, const wchar_t * methodName)
      : m_level(level)
      , m_out(out)
      , m_name(methodName)
    {
        gLogger.log(m_level, m_out, std::wstring(kIndention * nestingLevel, L'='), L">> ", m_name);
        ++nestingLevel;
    }

    ~FunctionLogger ()
    {
        --nestingLevel;
        gLogger.log(m_level, m_out, L"<<", std::wstring(kIndention * nestingLevel, L'='), L" ", m_name);
    }

    LogLevel m_level;
    std::wostream & m_out;
    const wchar_t * m_name;

    static const unsigned short kIndention = 2;
    static unsigned short nestingLevel;
};

#ifdef MAIN_CPP
unsigned short FunctionLogger::nestingLevel = 1;
#endif

#define LOG_FUNCTION(stream, fnname) FunctionLogger _fnLogger (LogLevel::kHigh, stream, fnname);
#define LOG_BUSY_FUNCTION(stream, fnname) FunctionLogger _fnLogger (LogLevel::kFirehose, stream, fnname);

} // namespace Go

#endif /* end of include guard: INCL_LOGGER_HPP__ */
