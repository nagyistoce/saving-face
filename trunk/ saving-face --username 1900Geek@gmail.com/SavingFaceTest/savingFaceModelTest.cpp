#include "stdafx.h"
#include "CppUnitTest.h"
#include "sf_model.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SavingFaceTest
{		
	TEST_CLASS(FirstTest)
	{
	public:

		
		
		TEST_METHOD(ModelTest1)
		{
			SF::Model *model = new SF::Model();
			Assert().Fail();
		}

	};
}