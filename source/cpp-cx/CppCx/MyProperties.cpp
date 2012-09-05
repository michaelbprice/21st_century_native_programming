#include "pch.h"
#include "MyProperties.h"
#include <stdexcept>

namespace CppCx { namespace Properties {

MyProperties::MyProperties ()
  : m_isValid(true)
  , m_loopCount(0)
{
    for (auto & row : m_board)
        for (auto & e : row)
            e = true;
}

bool MyProperties::Board_ReadOnly::get (size_t row, size_t col)
{
    try
    {
        return m_board[row][col];
    }
    catch (const std::out_of_range &)
    {
        throw ref new Platform::InvalidArgumentException();
    }
}

} } // namespace CppCx::Properties
