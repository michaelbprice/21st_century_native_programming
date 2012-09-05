#include "pch.h"
#include "CppUnitTest.h"

using namespace CppCx::Properties;
using namespace Platform;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CppCxTest
{
	TEST_CLASS(TestProperties)
	{
	public:
		
		TEST_METHOD(TestThemProperties)
		{
			MyProperties ^ props = ref new MyProperties();

            props->Name_ReadWrite = "C++";
            Assert::AreEqual("C++", props->Name_ReadWrite);

            Assert::AreEqual(true, props->IsValid_ReadOnly);
            
            props->LoopCount_WriteOnly = 10;

            Assert::AreEqual(true, props->Board_ReadOnly[3, 7]);
            Assert::ExpectException<InvalidArgumentException^>([props](){ props->Board_ReadOnly[10, 0]; });
		}

	};
}