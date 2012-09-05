#include "pch.h"
#include "CppUnitTest.h"

using namespace CppCx::Interfaces;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CppCxTest
{
	TEST_CLASS(TestInterfaces)
	{
	public:
		
		TEST_METHOD(TestInterfaceInheritance)
		{
			MyImplementation ^ impl = ref new MyImplementation();

            ISomeOtherInterface ^ other = impl;

            IMyDerivedInterface ^ derived = impl;
            IMyInterface ^ my_from_derived = derived;
            IMyInterface ^ my_from_impl = impl;
		}

	};
}