
#include "pch.h"
#include "MyGenerics.h"
#include <iostream>

using namespace std;
using namespace Platform;

void MyObjectPrinter::Print(Object ^ thing)
{
    if (thing == nullptr)
        wcout << L"{null Object}" << endl;
    else
        wcout << thing->ToString()->Data() << endl;
}

void MyStringPrinter::Print(Platform::String ^ thing)
{
    if (thing == nullptr)
        wcout << L"{null String}" << endl;
    else
        wcout << thing->Data() << endl;
}

void MyIntPrinter::Print(int thing)
{
    wcout << thing << endl;
}

void MyDoublePrinter::Print(double thing)
{
    wcout << thing << endl;
}
