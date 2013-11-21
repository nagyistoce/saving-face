#include "stdafx.h"
#include "CppUnitTest.h"
#include "sf_sdk_session.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SavingFaceTest
{
	void getYPR(SF::SF_YPR *ypr)
	{
		static char str[200];
		sprintf_s(str, "YPR::\t%f,\t%f,\t%f\n", ypr->yaw, ypr->pitch, ypr->roll);
		Logger().WriteMessage(str);
	}

	void getdepth(const char *test)
	{
		static char str[200];
		//sprintf_s(str, "YPR::\t%f,\t%f,\t%f\n", ypr->yaw, ypr->pitch, ypr->roll);
		Logger().WriteMessage(str);
	}

	void getLandmark(SF::SF_R3_COORD *landmark)
	{
		static char str[200];
		sprintf_s(str, "Nose::\t%f,\t%f,\t%f\n", landmark->x, landmark->y, landmark->z);
		Logger().WriteMessage(str);
	}

	TEST_CLASS(sdkSessionTest)
	{
	public:
		SF::SF_Session *session;

		void startSession()
		{
			
			session = new SF::SF_Session();
			if(!(session->createSession()))
				Assert().Fail(L"Failed To Create Session");			
			if(!(session->setOptions(NULL, NULL)))
				Assert().Fail(L"Failed to set Options");
			if(session->captureStreams() < SF_STS_OK)
				Assert().Fail(L"Failed To Locate and Capture Streams");
			session->createDepthRenderView();
			session->createColorRenderView();
			session->loadFaceModule();
		}


		TEST_METHOD(sdkSessionConstructorTest)
		{
			SF::SF_Session *session = new SF::SF_Session();
			Assert().IsNotNull(session);
			delete session;
		}


		TEST_METHOD(sdkYPRTest)
		{
			//Pass or Fail
			//Can't fully test without pre-recorded video.
			startSession();
			session->tempYPRLoop(&SavingFaceTest::getYPR,&SavingFaceTest::getLandmark);	
		}

		TEST_METHOD(sdkVerticesTest)
		{
			startSession();
			session->tempGetVertices(&SavingFaceTest::getYPR,&SavingFaceTest::getLandmark, &SavingFaceTest::getdepth);	
		}
	};
}