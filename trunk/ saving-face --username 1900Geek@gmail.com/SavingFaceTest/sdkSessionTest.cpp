#include "stdafx.h"
#include "CppUnitTest.h"
#include "sf_sdk_session.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SavingFaceTest
{
	void getYPR(SF::SF_YPR *ypr)
		{
			static char str[200];
			sprintf_s(str, "YPR:: %f, %f, %f\n", ypr->yaw, ypr->pitch, ypr->roll);
			Logger().WriteMessage(str);
		}

	TEST_CLASS(sdkSessionTest)
	{
	public:
		SF::SF_Session *session;

		void startSession()
		{
			session = new SF::SF_Session();
			//modelBuilder = new SF::sf_model_builder();

			if(!(session->createSession()))
				Assert().Fail();			
			if(!(session->setOptions(NULL, NULL)))
				Assert().Fail();
			if(!(session->captureStreams()))
				Assert().Fail();
			session->createDepthRenderView();
			session->createColorRenderView();
			session->loadFaceModule();
		}


		TEST_METHOD(sdkSessionConstructorTest)
		{
			// TODO: Your test code here
			Assert().Fail();
		}


		TEST_METHOD(sdkYPRTest)
		{
			startSession();
			session->tempYPRLoop(&SavingFaceTest::getYPR);
			Assert().Fail();
			
		}
		
		
	};

	
}