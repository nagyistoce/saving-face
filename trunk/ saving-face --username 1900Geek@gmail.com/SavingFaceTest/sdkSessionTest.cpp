#include "stdafx.h"
#include "CppUnitTest.h"
#include "sf_sdk_session.h"

#define Mathematica//Comment out this line to disable export.
#ifdef Mathematica
#include <fstream>
#include "sf_util.h"
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SavingFaceTest
{
	void getYPR(SF::SF_YPR *ypr, SF::SF_R3_COORD *nose)
	{
		static char str[200];
		sprintf_s(str, "YPR::\t%f,\t%f,\t%f Nose::\t%f,\t%f,\t%f\n", ypr->yaw, ypr->pitch, ypr->roll,nose->x,nose->y,nose->z);
		Logger().WriteMessage(str);
	}

	void getdepth(const char *test)
	{
		static bool doOnce = true;
		if(doOnce)		
			Logger().WriteMessage(test);
		doOnce = false;
	}
	
	//Obsolete
	void getLandmark(SF::SF_R3_COORD *landmark)
	{
		static char str[200];
		sprintf_s(str, "Nose::\t%f,\t%f,\t%f\n", landmark->x, landmark->y, landmark->z);
		Logger().WriteMessage(str);
	}

	void processVertex(SF::SF_R3_COORD &vertex)
	{
		static int i = 0;
		//Have too limit output. Gets huge fast.
		if(i < 1000){
			static char str[200];
			sprintf_s(str, "Vertex::\t%f,\t%f,\t%f\n", vertex.x, vertex.y, vertex.z);
			Logger().WriteMessage(str);
			i++;
		}
	}

#ifdef Mathematica
		ofstream *fs;

		void onNewFrame(int frame)
		{
			if(fs){
				fs->close();
				delete fs;
			}
			if(!SF::doesDirectoryExist("math_out"))
				SF::makeDirectory("math_out");
			char fileName[200];
			sprintf_s(fileName,200, "%stest%d.csv",SF::getFullPath("math_out").c_str(),frame);
			//sprintf_s(fileName,200, "test%d.csv",frame);
			Logger().WriteMessage(fileName);
			fs = new ofstream(fileName);
		}

		void saveYPR(SF::SF_YPR *ypr, SF::SF_R3_COORD *nose)
		{
			char str[200];
			sprintf_s(str,200,"%f,%f,%f\n%f,%f,%f\n",ypr->yaw,ypr->pitch,ypr->roll,nose->x,nose->y,nose->z);
			fs->write(str,strlen(str));
		}

		void saveVertex(SF::SF_R3_COORD &vertex)
		{
				static char str[200];
				sprintf_s(str,200,"%f,%f,%f\n", vertex.x, vertex.y, vertex.z);
				fs->write(str,strlen(str));
		}
#endif

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

		//NOTE:: Test will run forever if the camera is present
		//Until it detects a valid face for 30 frames.
		TEST_METHOD(sdk_YPR_Vertex_Test)
		{
			startSession();
			session->camera_loop(&getYPR,&processVertex,NULL,NULL,NULL,100);
			
		}

#ifdef Mathematica

		TEST_METHOD(ExportToCSV)
		{
			startSession();
			session->camera_loop(&saveYPR,&saveVertex,NULL,*onNewFrame,NULL,30);
		}
#endif


	};
}