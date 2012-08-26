#include "pch.h"
#include "MyDelegateAndEvent.h"

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;

MyDelegateAndEvent::MyDelegateAndEvent ()
{
    m_names = ref new Vector<String ^>();

    m_names->VectorChanged += ref new VectorChangedEventHandler<String^>([this](IObservableVector<String^> ^ sender, 
                                                                                IVectorChangedEventArgs ^ event)
    {
        //  The 'this' pointer is captured by strong-reference... careful now...
        //
        this->Changed();
    });
}