#include "pch.h"
#include "MyExceptions.h"

#include <stdexcept>

namespace CppCx { namespace Exceptions {

void Thrower::ThrowCppException ()
{
    throw std::out_of_range("Out of range, Fool!");
}

void Thrower::ThrowCustomException ()
{
    throw ref new Platform::COMException(E_NOT_SET, "Customized!");
}

void Thrower::ThrowWinRtException ()
{
    throw ref new Platform::NotImplementedException("Does not exist");
}

} } // namespace CppCx::Exceptions
