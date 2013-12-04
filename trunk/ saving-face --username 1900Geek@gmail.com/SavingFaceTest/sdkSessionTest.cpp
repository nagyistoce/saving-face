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
	void getYPR(SF::SF_YPR *ypr, SF::SF_R3_COORD *nose,void*)
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
	

	void processVertex(SF::SF_R3_COORD &vertex,void*)
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

		void saveYPR(SF::SF_YPR *ypr, SF::SF_R3_COORD *nose,void*)
		{ 
			char str[200];
			sprintf_s(str,200,"%f,%f,%f\n%f,%f,%f\n",ypr->yaw,ypr->pitch,ypr->roll,nose->x,nose->y,nose->z);
			fs->write(str,strlen(str));
		}

		void saveVertex(SF::SF_R3_COORD &vertex,void*)
		{
				static char str[200];
				sprintf_s(str,200,"%f,%f,%f\n", vertex.x, vertex.y, vertex.z);
				fs->write(str,strlen(str));
		}
#endif

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
			session->camera_loop(&getYPR,&processVertex,NULL,NULL,NULL,NULL,100);
			session->releaseStreams();
		}

		//NOTE:: Test will run forever if the camera is present
		//Until it detects a valid face for 30 frames.
		TEST_METHOD(saveVideoTest)
		{
			session = new SF::SF_Session();
			if(!(session->createSession()))
				Assert().Fail(L"Failed To Create Session");			
			if(!(session->setOptions(NULL, NULL)))
				Assert().Fail(L"Failed to set Options");
			if(session->captureStreams("BobIsYourUncle.vdo",true) < SF_STS_OK)
				Assert().Fail(L"Failed To Locate and Capture Streams");
			session->createDepthRenderView();
			session->createColorRenderView();
			session->loadFaceModule();
			session->camera_loop(&getYPR,&processVertex,NULL,NULL,NULL,NULL,100);

			Assert().IsTrue(doesDirectoryExist(getFullPath(_DEFAULT_VIDEO_DIR)), L"Directory does not exist.");
			string filePath = getFullPath(_DEFAULT_VIDEO_DIR) + "BobIsYourUncle.vdo";
			Assert().IsTrue(doesDirectoryExist(filePath), L"File does not exist.");
			session->releaseStreams();
		}

		TEST_METHOD(playbackVideoTest)
		{
			Assert().IsTrue(doesDirectoryExist(getFullPath(_DEFAULT_VIDEO_DIR)), L"Directory does not exist.");
			string filePath = getFullPath(_DEFAULT_VIDEO_DIR) + "BobIsYourUncle.vdo";
			Assert().IsTrue(doesDirectoryExist(filePath), L"File does not exist.");
			
			session = new SF::SF_Session();
			if(!(session->createSession()))
				Assert().Fail(L"Failed To Create Session");			
			if(!(session->setOptions(NULL, NULL)))
				Assert().Fail(L"Failed to set Options");
			if(session->captureStreams("BobIsYourUncle.vdo",false) < SF_STS_OK)
				Assert().Fail(L"Failed To Locate and Capture Streams");
			session->createDepthRenderView();
			session->createColorRenderView();
			session->loadFaceModule();
			session->camera_loop(&getYPR,&processVertex,NULL,NULL,NULL,NULL,90);
		}

		TEST_METHOD(savePhoto)
		{
			SF_Session session;
			session.createSession();
			session.setOptions(NULL,NULL);
			Model model;
			model.setName("Mr.","Fancy","","Pants","");
			session.snapshotLoop(&model,&shutterTest,&photoFinish);
			string path = getFullPath(_DEFAULT_IMAGE_DIR) + model.getFileVersionName() + ".BMP";
			Assert().IsTrue(doesDirectoryExist(path),L"File Not Saved");

		}

#ifdef Mathematica

		TEST_METHOD(ExportToCSV)
		{
			startSession();
			session->camera_loop(&saveYPR,&saveVertex,NULL,*onNewFrame,NULL,NULL,30);
			session->releaseStreams();
		}
#endif


	};
}