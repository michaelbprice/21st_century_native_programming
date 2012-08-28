#ifndef INCL_MYCASTING_H
#define INCL_MYCASTING_H

namespace CppCx { namespace Casting {

public value struct MyValueType
{
    int member;
};

public interface class MyInterfaceType
{
};

public interface class MyOtherInterfaceType
{
};

public ref class MyRefType : public MyInterfaceType
{
};

public ref class MyDerivedRefType sealed : public MyRefType
{
};

} } // namespace CppCx::Casting

#endif // INCL_MYCASTING_H