#ifndef INCL_MYDELEGATEANDEVENT_H
#define INCL_MYDELEGATEANDEVENT_H

#include <vector>
#include "collection.h"

delegate void OnChanged ();

ref class MyDelegateAndEvent sealed
{
public:
    MyDelegateAndEvent ();

    event OnChanged ^ Changed;

private:
    Platform::Collections::Vector<Platform::String ^> ^ m_names;
};

#endif // INCL_MYDELEGATEANDEVENT_H