#include "stdafx.h"
#include "CppUnitTest.h"
#include "sf_tr_func.h"
#include "sf_defs.h"
#include "pxcdefs.h"
#include "sf_model.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SavingFaceTest
{
	TEST_CLASS(transformFunctionsTest)
	{
	public:
		SF::SF_TR_MATRIX tm;

		TEST_METHOD(testCalculateTrMatrix)
		{
			//Test is taking entirely too long. find out why.
			//Reason is it is the first test run.
			//at 1 Million calls only increases by 1 sec run time.
			PXCPoint3DF32 trv = {1,1,1};
			SF::SF_YPR ypr = {0,0,0};
			for(int i = 1; i < 1000000; i++)
				SF::calculateTRMatrix(tm,trv, ypr);
			SF::SF_TR_MATRIX exp;
			exp.trV.x = 1;
			exp.trV.y = 1;
			exp.trV.z = 1;
			exp.rotMTX[0] = 1;
			exp.rotMTX[1] = 0;
			exp.rotMTX[2] = 0;
			exp.rotMTX[3] = 0;
			exp.rotMTX[4] = 1;
			exp.rotMTX[5] = 0;
			exp.rotMTX[6] = 0;
			exp.rotMTX[7] = 0;
			exp.rotMTX[8] = 1;
			char *str = new char[200];
			sprintf(str, "Translation Vector::\n%f, %f, %f\n", tm.trV.x,tm.trV.y,tm.trV.z);
			Logger::WriteMessage(str);
			sprintf(str, "Rotation Matrix Contains::\n%f, %f, %f\n%f, %f, %f\n%f, %f, %f", 
				tm.rotMTX[0],
				tm.rotMTX[1],
				tm.rotMTX[2],
				tm.rotMTX[3],
				tm.rotMTX[4],
				tm.rotMTX[5],
				tm.rotMTX[6],
				tm.rotMTX[7],
				tm.rotMTX[8]
			);
			Logger::WriteMessage(str);
			Assert().AreEqual(memcmp(&(tm.trV),&(exp.trV),sizeof(float)*3),0,L"Translation Vector Fail");
			delete[] str;
			//Add a test that calculates a rotation matrix with another known output.
		}

		TEST_METHOD(testVectorTranslation)
		{
			//SF::translateCoord();
			Assert().Fail();
		}

		TEST_METHOD(testVectorRotation)
		{
			//SF::rotateCoord();
			Assert().Fail();
		}

		TEST_METHOD(testVectorTransform)
		{
			//SF::transformCoord();
			Assert().Fail;
		}

		TEST_METHOD(testMtxMult1b3)
		{
			SF::SF_MODEL_COORD3D out;
			SF::SF_TR_MATRIX matrix;
			SF::SF_R3_COORD tr_coord3d;

			matrix.rotMTX[0] = 3;
			matrix.rotMTX[1] = 1;
			matrix.rotMTX[2] = 3;
			matrix.rotMTX[3] = 1;
			matrix.rotMTX[4] = 3;
			matrix.rotMTX[5] = 1;
			matrix.rotMTX[6] = 3;
			matrix.rotMTX[7] = 1;
			matrix.rotMTX[8] = 3;

			tr_coord3d.x = 1;
			tr_coord3d.y = 2;
			tr_coord3d.z = 3;


			char *str = new char[200];

			SF::MatrixMultiply1b3(out, tr_coord3d, matrix);

			sprintf(str, "Output Matrix Contains::\n%f, %f, %f", 
				out.x,
				out.y,
				out.z
			);
			Logger::WriteMessage(str);
			delete[] str;

			if (out.x != 14 || out.y != 10 || out.z != 14)
			{
				Assert().Fail();
			}
			
		}

		TEST_METHOD(testMtxMult3b3)
		{
			SF::SF_SCALAR in1[9] ={3,1,3,1,3,1,3,1,3}, in2[9] = {3,2,2,3,2,2,3,2,5}, out[9];
			char *str = new char[200];
			//memset(in1,2.0f,sizeof(float)*9);
			//memset(in2,3.0f,sizeof(float)*9);
			//memset(out,0.0f,sizeof(float)*9);
			SF::MatrixMultiply3b3(out,in1,in2);
			sprintf(str, "Output Matrix Contains::\n%f, %f, %f\n%f, %f, %f\n%f, %f, %f", 
				out[0],
				out[1],
				out[2],
				out[3],
				out[4],
				out[5],
				out[6],
				out[7],
				out[8]
			);
			Logger::WriteMessage(str);
			delete[] str;

			if (out[0] != 21 || out[1] != 14 || out[2] != 23 || out[3] != 15 || out[4] != 10 || out[5] != 13 || out[6] != 21 || out[7] != 14 || out[8] != 23)
			{
				Assert().Fail();
			}
		}


		TEST_METHOD(testCoordInModelSpace)
		{
			SF::Model *model = new SF::Model();
			SF::SF_MODEL_COORD3D_INDEX index;

			SF::SF_MODEL_COORD3D coord3d;
			SF::Model::Model_Info const *info = model->getModelInfo();

			coord3d.x = info->xMin;
			coord3d.y = info->yMin;
			coord3d.z = info->zMin;

			SF::coordInModelSpace(index, coord3d, info);

			char *str = new char[200];
			
			sprintf(str, "Output Model Coord3d Index Contains::\n%f, %f, %f", 
				index.x,
				index.y,
				index.z
			);
			Logger::WriteMessage(str);
			delete[] str;
			delete model;
			delete info;

			if (index.x != 0 || index.y != 0 || index.z != 0)
			{
				Assert().Fail();
			}
		}

	};
}