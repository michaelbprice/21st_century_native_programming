#include "pch.h"
#include "CppUnitTest.h"
#include <Windows.h>
#include <stdexcept>

using namespace CppCx::Exceptions;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Platform;

namespace CppCxTest
{
	TEST_CLASS(TestExceptions)
	{
	public:
		
		TEST_METHOD(ThrowingCppExceptionShouldResultInFailureException)
		{
			Thrower thrower;

            // TODO: This crashes on VS 2012 RC
            //Assert::ExpectException<std::out_of_range>([&](){ thrower.ThrowCppException(); });
        }

		TEST_METHOD(ThrowingWinRtExceptionShouldSucceed)
		{
			Thrower thrower;

            Assert::ExpectException<NotImplementedException^>([&](){ thrower.ThrowWinRtException(); });
        }

		TEST_METHOD(ThrowingCustomExceptionShouldSucceed)
		{
			Thrower thrower;

            try
            {
                thrower.ThrowCustomException();
                Assert::Fail();
            }
            catch (COMException^ cex)
            {
                Assert::AreEqual(static_cast<int>(E_NOT_SET), cex->HResult);
            }
        }
	};
}