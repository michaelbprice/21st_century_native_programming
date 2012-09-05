#include "pch.h"
#include "CppUnitTest.h"

using namespace CppCx::DelegateAndEvent;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CppCxTest
{
	TEST_CLASS(TestDelegateAndEvent)
	{
	public:
		
		TEST_METHOD(DelegateShouldNotBeCalledWhenNoChange)
		{
            bool wasCalled = false;

			MyDelegateAndEvent ^ test = ref new MyDelegateAndEvent(ref new ChangedEventHandler([&wasCalled]()
            {
                wasCalled = true;
            }));

            Assert::IsFalse(wasCalled);
		}

		TEST_METHOD(DelegateShouldBeCalledWhenChangeHappens)
		{
            bool wasCalled = false;

			MyDelegateAndEvent ^ test = ref new MyDelegateAndEvent(ref new ChangedEventHandler([&wasCalled]()
            {
                wasCalled = true;
            }));

            test->AddString("Hello");
            Assert::IsTrue(wasCalled);
		}
	};
}