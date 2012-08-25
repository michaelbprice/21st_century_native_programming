//
// http://msdn.microsoft.com/en-us/library/windows/apps/hh699861.aspx
//

#ifndef INCL_MYVALUETYPE_H
#define INCL_MYVALUETYPE_H

// A dummy type
//
struct MyCppType
{ };

// There is not very many reasons to make a WinRT value type be a class, as you
// cannot have any public methods and they cannot be derived from (see errors C3417, C3983, C3194)
//
value struct MyValueType
{
    int m_integer;
    Platform::String ^ m_string;

    //MyCppType m_cppType;    // errors C3986 and C3992
};

// Derivation with value types are a bit futile; they cannot be a base and
// they can only derive from interfaces, although they cannot implement the
// interface because they cannot have public methods
//
interface struct IStructInterface
{
    //bool m_valid;       //  errorz C2844 and C3984
    //bool IsValid ();    // causes error C3246
};

ref class MyInheritedValueType : public IStructInterface
{ };

#endif // INCL_MYVALUETYPE_H
