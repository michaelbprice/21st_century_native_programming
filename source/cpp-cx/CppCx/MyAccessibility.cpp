#include "pch.h"
#include "MyAccessibility.h"
#include <string>

namespace CppCx { namespace Accessibility {

using namespace std;
using namespace Platform;

MyPublicType::MyPublicType (String ^ name)
    : m_defaultName(name->Data(), name->Length())
    , m_nameForMyChildren(L"Papa Bear")
{ }

String ^ MyPublicType::GetDefaultName ()
{
    return ref new String(m_defaultName.c_str(), m_defaultName.length());
}

void MyPublicType::SetDefaultName (String ^ name)
{
    m_defaultName = wstring(name->Data(), name->Length());
}

const std::wstring & MyPublicType::GetInternalNameThatCSharpCannot ()
{
    return m_defaultName;
}

Platform::String ^ MyPublicType::GetNameForChildren ()
{
    return ref new String(m_nameForMyChildren.c_str(), m_nameForMyChildren.length());
}


} } // namespace CppCx::Accessiblity