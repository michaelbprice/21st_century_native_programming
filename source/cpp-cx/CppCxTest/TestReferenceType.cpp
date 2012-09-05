#include "pch.h"
#include "CppUnitTest.h"

using namespace CppCx::ReferenceType;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CppCxTest
{
	TEST_CLASS(TestReferenceType)
	{
	public:
		
        TEST_METHOD(TestCopySemantics)
        {
            MyReferenceType ^ one = ref new MyReferenceType();
            one->Integer = 1;
            one->TheString = "Hello";

            MyReferenceType ^ two = one;

            two->Integer = 0;
            two->TheString = "World";

            Assert::AreEqual(one->Integer, two->Integer);
            Assert::AreEqual(one->TheString, two->TheString);
        }

        TEST_METHOD(TestStackObject)
        {
            MyReferenceType one;
            one.Integer = 1;
            one.TheString = "Hello";

            Assert::AreEqual(1, one.Integer);
            Assert::AreEqual("Hello", one.TheString);
        }
	};
}