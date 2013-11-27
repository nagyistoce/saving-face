#include "stdafx.h"
#include "CppUnitTest.h"
#include "sf_sdk_session.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SavingFaceTest
{
	bool shutterTest()
	{
		static int i = 0;
		return (++i == 80);
	}
	bool photoFinish()
	{
		static int i = 0;
		return (++i == 100);
	}

	TEST_CLASS(controllerTest)
	{
	public:
		
		TEST_METHOD(savePhoto)
		{
			SF_Session session;
			session.createSession();
			session.setOptions(NULL,NULL);
			Model model;
			model.setName("Mr.","Fancy","","Pants","");
			session.snapshotLoop(&model,&shutterTest,&photoFinish);

			Assert().Fail(L"Not Finished");
		}

	};
}