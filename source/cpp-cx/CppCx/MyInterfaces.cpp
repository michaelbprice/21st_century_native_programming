#include "pch.h"
#include "MyInterfaces.h"
#include <algorithm>
#include <iterator>

using namespace std;
using namespace Platform;

namespace CppCx { namespace Interfaces {

void MyImplementation::Finish (String ^ id)
{
    m_completed->Append(id);

    OnFinished(id);
}

bool MyImplementation::IsFinished (String ^ id)
{
    auto result = find(begin(m_completed), end(m_completed), id);

    return result != end(m_completed);
}

} } // namespace CppCx::Interfaces
