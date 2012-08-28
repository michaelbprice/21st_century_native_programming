#include "pch.h"
#include "MyDelegateAndEvent.h"

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;

namespace CppCx { namespace DelegateAndEvent {

MyDelegateAndEvent::MyDelegateAndEvent (ChangedEventHandler ^ onChanged)
{
    Changed += onChanged;

    m_names = ref new Vector<String ^>();

    m_names->VectorChanged += ref new VectorChangedEventHandler<String^>([this](IObservableVector<String^> ^ sender, 
                                                                                IVectorChangedEventArgs ^ event)
    {
        //  The 'this' pointer is captured by strong-reference... careful now...
        //
        this->Changed();
    });
}

void MyDelegateAndEvent::AddString (String ^ s)
{
    m_names->Append(s);
}

} } // namespace CppCx::DelegateAndEvent
