#include "pch.h"
#include "CppUnitTest.h"

using namespace CppCx::Casting;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Platform;

namespace CppCxTest
{
	TEST_CLASS(TestCasting)
	{
	public:
		
		TEST_METHOD(CastingToValueTypeShouldFail)
		{
            MyDerivedRefType ^ x;

            //static_cast<MyValueType>(x);
            //dynamic_cast<MyValueType>(x);
            //safe_cast<MyValueType>(x);
            //reinterpret_cast<MyValueType>(x);
		}

        TEST_METHOD(CastingToBaseTypeShouldSucceed)
        {
            MyDerivedRefType ^ x = ref new MyDerivedRefType();

            static_cast<MyRefType^>(x);
            Assert::IsNotNull(dynamic_cast<MyRefType^>(x));
            Assert::IsNotNull(safe_cast<MyRefType^>(x));
            Assert::IsNotNull(reinterpret_cast<MyRefType^>(x));
        }

        TEST_METHOD(CastingToBaseInterfaceShouldSucceed)
        {
            MyDerivedRefType ^ x = ref new MyDerivedRefType();

            static_cast<MyInterfaceType^>(x);
            Assert::IsNotNull(dynamic_cast<MyInterfaceType^>(x));
            Assert::IsNotNull(safe_cast<MyInterfaceType^>(x));
            Assert::IsNotNull(reinterpret_cast<MyInterfaceType^>(x));
        }

        TEST_METHOD(CastingToOtherInterfaceShouldFail)
        {
            MyDerivedRefType ^ x = ref new MyDerivedRefType();

            // static_cast<MyOtherInterfaceType^>(x);
            Assert::IsNull(dynamic_cast<MyOtherInterfaceType^>(x));
            Assert::ExpectException<InvalidCastException^>([&](){ safe_cast<MyOtherInterfaceType^>(x);});
            Assert::IsNotNull(reinterpret_cast<MyOtherInterfaceType^>(x));
        }

        TEST_METHOD(DownCastingToDerivedShouldSucceed)
        {
            MyRefType ^ x = ref new MyDerivedRefType();

            static_cast<MyDerivedRefType^>(x);
            Assert::IsNotNull(dynamic_cast<MyDerivedRefType^>(x));
            Assert::IsNotNull(safe_cast<MyDerivedRefType^>(x));
            Assert::IsNotNull(reinterpret_cast<MyDerivedRefType^>(x));
        }

        TEST_METHOD(DownCastingToSiblingShouldFail)
        {
            MyRefType ^ x = ref new MyDerivedRefType();

            //static_cast<MyDerivedRefType^>(x);
            //Assert::IsNotNull(dynamic_cast<MyDerivedRefType^>(x));
            //Assert::IsNotNull(safe_cast<MyDerivedRefType^>(x));
            //Assert::IsNotNull(reinterpret_cast<MyDerivedRefType^>(x));
        }
    };
}