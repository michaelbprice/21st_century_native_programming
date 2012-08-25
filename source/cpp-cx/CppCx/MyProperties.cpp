#include "pch.h"
#include "MyProperties.h"

bool MyProperties::Board_ReadOnly::get (size_t row, size_t col)
{
    return m_board[row][col];
}
