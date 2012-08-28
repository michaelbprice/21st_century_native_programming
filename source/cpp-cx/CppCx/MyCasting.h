#ifndef INCL_MYCASTING_H
#define INCL_MYCASTING_H

namespace CppCx { namespace Casting {

value struct MyValueType
{
    int member;
};

interface class MyInterfaceType
{
};

interface class MyOtherInterfaceType
{
};

ref class MyRefType : public MyInterfaceType
{
};

ref class MyDerivedRefType sealed : public MyRefType
                                  , public MyOtherInterfaceType
{
};

} } // namespace CppCx::Casting

#endif // INCL_MYCASTING_H