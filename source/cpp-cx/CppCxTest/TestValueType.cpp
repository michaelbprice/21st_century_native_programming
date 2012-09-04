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

	};
}