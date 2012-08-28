#ifndef INCL_MYACCESSIBILITY_H
#define INCL_MYACCESSIBILITY_H

#include <string>

struct SomeCppType
{ };

namespace CppCx { namespace Accessibility {

// Will generate WinRT metadata
//
public ref class MyPublicType
{

// Public C++ accessibility, public WinRT metadata
// *** Normal C++ types not allowed ***
//
public:
    //wchar_t * GetDefaultName (); // error C3992: 'GetDefaultName': signature of public member contains invalid type 'wchar_t *'
    Platform::String ^ GetDefaultName ();


// Protected C++ accessibility, protected WinRT metadata
// *** Normal C++ types not allowed ***
//
protected:
    void SetDefaultName (Platform::String ^ name);


// Private C++ accessibility, no WinRT metadata
// *** Normal C++ types allowed ***
//
private:
    std::wstring m_defaultName;
    MyPublicType (Platform::String ^ name);


// ********************* HERE'S WHERE IT GETS COMPLICATED *********************


// Public C++ accessibility, no WinRT metadata
// *** Normal C++ types allowed ***
//
internal: // or private public:
    const std::wstring & GetInternalNameThatCSharpCannot ();


// Public C++ accessibility, protected WinRT metadata
// *** Normal C++ types not allowed ***
//
public protected: // or protected public:
    Platform::String ^ GetNameForChildren ();


// Protected C++ accessibility, no WinRT metadata
// *** Normal C++ types allowed ***
//
protected private: // or private protected:
    std::wstring m_nameForMyChildren;
};

// No WinRT metadata
//
private ref class MyPrivateType // or no accessibility modifier
{
public:
    //SomeCppType PublicGetCppType ();

};

}  } // namespace CppCx::Accessibility


public ref class MyInvalidType
{ };

#endif // INCL_MYACCESSIBILITY_H