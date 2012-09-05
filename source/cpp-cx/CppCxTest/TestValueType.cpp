#include "pch.h"
#include "CppUnitTest.h"

using namespace CppCx::ValueType;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CppCxTest
{
	TEST_CLASS(TestValueType)
	{
	public:
		
		TEST_METHOD(TestAccessibility)
		{
			MyValueType v = {1, "Hello" };

            Assert::AreEqual(1, v.m_integer);
            Assert::AreEqual("Hello", v.m_string);
		}

        TEST_METHOD(TestCopySemantics)
        {
            MyValueType one = {1, "Hello"};
            MyValueType two = one;

            two.m_integer = 0;
            two.m_string = "World";

            Assert::AreNotEqual(one.m_integer, two.m_integer);
            Assert::AreNotEqual(one.m_string, two.m_string);
        }

	};
}