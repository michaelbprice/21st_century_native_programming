
#ifndef INCL_MYINTERFACES_H
#define INCL_MYINTERFACES_H

#include <collection.h>

namespace CppCx { namespace Interfaces {

public delegate void FinishedEventHandler (Platform::String ^ id);

public interface class IMyInterface
{
    void Finish (Platform::String ^id);

    bool IsFinished (Platform::String ^ id);

    event FinishedEventHandler ^ OnFinished;
};

public interface class IMyDerivedInterface : public IMyInterface
{
    property Platform::String ^ Name;
};

public interface class ISomeOtherInterface
{
};

public ref class MyImplementation sealed : public IMyDerivedInterface
                                         , public ISomeOtherInterface
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

} } // namespace CppCx::Interfaces

#endif // INCL_MYINTERFACES_H
