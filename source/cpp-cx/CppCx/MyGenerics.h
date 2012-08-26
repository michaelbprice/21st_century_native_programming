#ifndef INCL_MYGENERICS_H
#define INCL_MYGENERICS_H

#include <iostream>

generic <typename T>
interface class IMyGenericPrinter
{
	void Print(T thing);
};

// Strategy #1: Implement the generic for every potential type
//
ref class MyObjectPrinter : IMyGenericPrinter<Platform::Object ^>
{
public:
    virtual void Print(Platform::Object ^ thing);
};

ref class MyStringPrinter : IMyGenericPrinter<Platform::String ^>
{
public:
    virtual void Print(Platform::String ^ thing);
};

ref class MyIntPrinter : IMyGenericPrinter<int>
{
public:
    virtual void Print(int thing);
};

ref class MyDoublePrinter : IMyGenericPrinter<double>
{
public:
    virtual void Print(double thing);
};


// Strategy #2: Use template machinary to implement the generic
//
template <typename T>
ref class MyPrinter : IMyGenericPrinter<T>
{
public:
    virtual void Print (T thing)
    { std::wcout << thing << std::endl; }
};

template <>
ref class MyPrinter<Platform::Object ^> : IMyGenericPrinter<Platform::Object ^>
{
public:
    virtual void Print (Platform::Object ^ thing)
    {
        if (thing == nullptr)
            std::wcout << L"{null Object}" << std::endl;
        else
            std::wcout << thing->ToString()->Data() << std::endl;
    }
};

template <>
ref class MyPrinter<Platform::String ^> : IMyGenericPrinter<Platform::String ^>
{
public:
    virtual void Print (Platform::String ^ thing)
    {
        if (thing == nullptr)
            std::wcout << L"{null String}" << std::endl;
        else
            std::wcout << thing->Data() << std::endl;
    }
};


// Strategy #2: Specialize just a helper function (less typing)
//
template <typename T>
void doPrint (T thing)
{
    std::wcout << thing << std::endl;
}

template <typename T>
ref class MyBetterPrinter : IMyGenericPrinter<T>
{
public:
    virtual void Print (T thing)
    { doPrint(thing); }
};

template <>
void doPrint<Platform::Object^> (Platform::Object ^ thing)
{
    if (thing == nullptr)
        std::wcout << L"{null Object}" << std::endl;
    else
        std::wcout << thing->ToString()->Data() << std::endl;
}

template <>
void doPrint<Platform::String ^> (Platform::String ^ thing)
{
    if (thing == nullptr)
        std::wcout << L"{null String}" << std::endl;
    else
        std::wcout << thing->Data() << std::endl;
}

#endif // INCL_MYGENERICS_H