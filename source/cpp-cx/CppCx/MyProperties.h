#ifndef INCL_MYPROPERTIES_H
#define INCL_MYPROPERTIES_H

#include <array>

namespace CppCx { namespace Properties {

    ref class MyProperties
    {
    public:
        // Implicitly backed, read-write
        //
        property Platform::String ^ Name_ReadWrite;

        // Explicitly backed, read-only
        //
        property bool IsValid_ReadOnly { bool get() { return m_isValid; } }

        // Explicitly backed, write-only
        //
        property int LoopCount_WriteOnly { void set (int value) { m_loopCount = value; } }

        // Explicitly backed, read-only, implementation out-of-line
        //
        property bool Board_ReadOnly[size_t, size_t] { bool get (size_t row, size_t col); }

    private:
        bool m_isValid;
        int m_loopCount;

        std::array<std::array<bool, 10>, 10> m_board;
    };

} } // namespace CppCx::Properties

#endif // INCL_MYPROPERTIES_H
