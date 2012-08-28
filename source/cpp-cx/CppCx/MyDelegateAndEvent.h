#ifndef INCL_MYDELEGATEANDEVENT_H
#define INCL_MYDELEGATEANDEVENT_H

#include <vector>
#include "collection.h"

namespace CppCx { namespace DelegateAndEvent {

public delegate void ChangedEventHandler ();

public ref class MyDelegateAndEvent sealed
{
public:
    MyDelegateAndEvent (ChangedEventHandler ^ onChanged);

    void AddString (Platform::String ^ s);

    event ChangedEventHandler ^ Changed;

private:
    Platform::Collections::Vector<Platform::String ^> ^ m_names;
};

} } // namespace CppCx::DelegateAndEvent

#endif // INCL_MYDELEGATEANDEVENT_H