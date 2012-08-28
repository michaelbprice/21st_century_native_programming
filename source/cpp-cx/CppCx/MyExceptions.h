#ifndef INCL_MYEXCEPTIONS_H
#define INCL_MYEXCEPTIONS_H

namespace CppCx { namespace Exceptions {

public ref class Thrower
{
public:
    void ThrowCppException ();
    void ThrowCustomException ();
    void ThrowWinRtException ();
};

} } // namespace CppCx::Exceptions

#endif // INCL_MYEXCEPTIONS_H