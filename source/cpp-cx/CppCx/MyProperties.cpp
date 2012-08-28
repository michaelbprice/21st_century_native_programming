#include "pch.h"
#include "MyProperties.h"

namespace CppCx { namespace Properties {

bool MyProperties::Board_ReadOnly::get (size_t row, size_t col)
{
    return m_board[row][col];
}

} } // namespace CppCx::Properties
