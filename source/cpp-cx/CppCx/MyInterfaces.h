
#ifndef INCL_MYINTERFACES_H
#define INCL_MYINTERFACES_H

#include <collection.h>

delegate void FinishedEventHandler (Platform::String ^ id);

interface class IMyInterface
{
    void Finish (Platform::String ^id);

    bool IsFinished (Platform::String ^ id);

    event FinishedEventHandler ^ OnFinished;
};

interface class IMyDerivedInterface : public IMyInterface
{
    property Platform::String ^ Name;
};

interface class ISomeOtherInterface
{
};

ref class MyImplementation : public IMyDerivedInterface, public ISomeOtherInterface
{
public:
    virtual property Platform::String ^ Name;
    virtual void Finish (Platform::String ^ id);
    virtual bool IsFinished (Platform::String ^ id);
    virtual event FinishedEventHandler ^ OnFinished;

private:
    Platform::String ^ m_name;
    Platform::Collections::Vector<Platform::String ^> ^ m_completed;
};

#endif // INCL_MYINTERFACES_H
