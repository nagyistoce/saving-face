

#include "stdafx.h"
#include "CppUnitTest.h"
#ifndef TEMP_DISABLE
#include "sf_tr_test.h"
#include "sf_defs.h"
#include "pxcdefs.h"
#include "sf_model.h"
#define _USE_MATH_DEFINES
#include "math.h"

#define ACCEPTABLE_ERROR  0.00001f

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SavingFaceTest
{
	TEST_CLASS(transformFunctionsTest)
	{
		

		bool withinTolerance3b3(SF::SF_TR_MATRIX const &tm, SF::SF_TR_MATRIX const &exp)
		{
			for(int i = 0; i < 9; i++)
				if(tm.rotMTX[i] > exp.rotMTX[i] + ACCEPTABLE_ERROR ||
					tm.rotMTX[i] < exp.rotMTX[i] - ACCEPTABLE_ERROR) 
					return false;
			return true;
		}

		void getArbitraryNumberTrMatrix(SF::SF_TR_MATRIX  &tm,SF::SF_TR_MATRIX &exp)
		{
			PXCPoint3DF32 trv = {3.5f,-1.3f,-1.2f};
			SF::SF_YPR ypr;
			ypr.yaw = 0.72f * (float)M_PI;
			ypr.pitch = 0.03f * (float)M_PI;
			ypr.roll = 0.95f * (float)M_PI;
			SFTEST::calculateTRMatrix(tm,trv, ypr);
			exp.trV.x = 3.5f;
			exp.trV.y = -1.3f;
			exp.trV.z = -1.2f;
			exp.rotMTX[0] = -0.9833049f;
			exp.rotMTX[1] = -0.1557402f;
			exp.rotMTX[2] = 0.09410831f;
			exp.rotMTX[3] = -0.171334f;
			exp.rotMTX[4] = 0.6182329f;
			exp.rotMTX[5] = -0.7670937f;
			exp.rotMTX[6] = 0.06128647f;
			exp.rotMTX[7] = -0.770411f;
			exp.rotMTX[8] = -0.6345951f;
		}

		void printTmMatrix(SF::SF_TR_MATRIX const &tm)
		{
			char *str = new char[200];
			sprintf_s(str, 200, "Translation Vector::\n%f, %f, %f\n", tm.trV.x,tm.trV.y,tm.trV.z);
			Logger::WriteMessage(str);
			sprintf_s(str, 200, "Rotation Matrix Contains::\n%f, %f, %f\n%f, %f, %f\n%f, %f, %f\n", 
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
		}


	public:
		SF::SF_TR_MATRIX tm;



		TEST_METHOD(testCalculateTrMatrix)
		{
			PXCPoint3DF32 trv = {1,1,1};
			SF::SF_YPR ypr = {0,0,0,0};
			for(int i = 1; i < 1000000; i++)
				SFTEST::calculateTRMatrix(tm,trv, ypr);
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
			printTmMatrix(tm);
			Assert().IsTrue(withinTolerance3b3(tm,exp),L"Matrix 1 fail");
			
			getArbitraryNumberTrMatrix(tm,exp);
			Logger().WriteMessage(L"\nActual Matrix\n");
			printTmMatrix(tm);
			Logger().WriteMessage(L"\nExpected Matrix\n");
			printTmMatrix(exp);
			Assert().IsTrue(withinTolerance3b3(tm,exp),L"Matrix 2 fail");
		
		}

		TEST_METHOD(testVectorTranslation){
			SF::SF_TR_MATRIX tr;
			SF::SF_R3_COORD origCoord, out, exp;

			origCoord.x = 10;
			origCoord.y = 15;
			origCoord.z = 20;

			tr.trV.x = 5;
			tr.trV.y = 10;
			tr.trV.z = 15;

			exp.x = 5;
			exp.y = 5;
			exp.z = 5;
			
			SFTEST::translateCoord(out, origCoord, tr);

			Assert().AreEqual(memcmp(&(out),&(exp),sizeof(float)*3),0,L"Translation Vector Fail");
		}

		TEST_METHOD(testVectorRotation){
			SF::SF_MODEL_COORD3D out, expMin, expMax;
			SF::SF_R3_COORD tr_coord3d;
			SF::SF_TR_MATRIX tm,tm_exp;

			tr_coord3d.x = 12;
			tr_coord3d.y = 8;
			tr_coord3d.z = 4;

			getArbitraryNumberTrMatrix(tm,tm_exp);

			expMin.x = -12.92519f - ACCEPTABLE_ERROR;
			expMin.y = -0.00466299f - ACCEPTABLE_ERROR;
			expMin.z = -7.54583f - ACCEPTABLE_ERROR;

			expMax.x = -12.92519f + ACCEPTABLE_ERROR;
			expMax.y = -0.00466299f + ACCEPTABLE_ERROR;
			expMax.z = -7.54583f + ACCEPTABLE_ERROR;

			SFTEST::rotateCoord(out, tr_coord3d, tm);

			char *str = new char[200];
			sprintf_s(str, 200, "Output From Rotate Coord::\n%f, %f, %f\n", out.x,out.y,out.z);
			Logger::WriteMessage(str);


			Assert().IsTrue(expMax.x >= out.x && out.x >= expMin.x);
			Assert().IsTrue(expMax.y >= out.y && out.y >= expMin.y);
			Assert().IsTrue(expMax.z >= out.z && out.z >= expMin.z);
		}

		TEST_METHOD(testVectorTransform)
		{ 
			SF::SF_MODEL_COORD3D out, expMin, expMax;
			SF::SF_R3_COORD tr_coord3d;
			SF::SF_TR_MATRIX tm, tm_exp;

			tr_coord3d.x = 10;
			tr_coord3d.y = 15;
			tr_coord3d.z = 20;

			getArbitraryNumberTrMatrix(tm,tm_exp);

			printTmMatrix(tm);

			expMin.x = -7.884954f - ACCEPTABLE_ERROR;
			expMin.y = -7.267827f - ACCEPTABLE_ERROR;
			expMin.z = -25.34534f - ACCEPTABLE_ERROR;

			expMax.x = -7.884954f + ACCEPTABLE_ERROR;
			expMax.y = -7.267827f + ACCEPTABLE_ERROR;
			expMax.z = -25.34534f + ACCEPTABLE_ERROR;

			SFTEST::transformCoord(out, tr_coord3d, tm);

			char *str = new char[200];
			sprintf_s(str, 200, "Output From Transform Coord::\n%f, %f, %f\n", out.x,out.y,out.z);
			Logger::WriteMessage(str);

			Assert().IsTrue(expMax.x >= out.x && out.x >= expMin.x);
			Assert().IsTrue(expMax.y >= out.y && out.y >= expMin.y);
			Assert().IsTrue(expMax.z >= out.z && out.z >= expMin.z);
		}

		TEST_METHOD(testMtxMult1b3)
		{
			SF::SF_MODEL_COORD3D out;
			SF::SF_MODEL_COORD3D exp;
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

			exp.x = 14;
			exp.y = 10;
			exp.z = 14;

			char *str = new char[200];

			SFTEST::MatrixMultiply1b3(out, tr_coord3d, matrix);

			sprintf_s(str, 200, "Output Matrix Contains::\n%f, %f, %f", 
				out.x,
				out.y,
				out.z
			);


			Logger::WriteMessage(str);
			delete[] str;

			Assert().AreEqual(memcmp(&out,&exp,sizeof(float)*3),0,L"1X3 Matrices Multiplication Fail");
		}

		TEST_METHOD(testMtxMult3b3)
		{
			SF::SF_SCALAR in1[9] ={3,1,3,1,3,1,3,1,3}, in2[9] = {3,2,2,3,2,2,3,2,5}, out[9], exp[9] = {21,14,23,15,10,13,21,14,23};
			char *str = new char[200];
			SFTEST::MatrixMultiply3b3(out,in1,in2);
			sprintf_s(str, 200, "Output Matrix Contains::\n%f, %f, %f\n%f, %f, %f\n%f, %f, %f", 
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

			Assert().AreEqual(memcmp(&out,&exp,sizeof(float)*3),0,L"3X3 Matrices Multiplication Fail");
		}


		TEST_METHOD(testCoordInModelSpace)
		{
			//Should add More testing here for other known coords
			//End points would be the ideal thing to check.
			SF::Model *model = new SF::Model();
			SF::SF_MODEL_COORD3D_INDEX index;

			SF::SF_MODEL_COORD3D coord3d;
			SF::Model::Model_Info const *info = model->getModelInfo();

			SF::SF_MODEL_COORD3D_INDEX exp;
			exp.x = 0;
			exp.y = 0;
			exp.z = 0;

			coord3d.x = info->xMin;
			coord3d.y = info->yMin;
			coord3d.z = info->zMin;

			SFTEST::coordInModelSpace(index, coord3d, info);

			char *str = new char[200];
			
			sprintf_s(str, 200, "Output Model Coord3d Index Contains::\n%d, %d, %d", 
				index.x,
				index.y,
				index.z
			);
			Logger::WriteMessage(str);
			delete[] str;
			delete model;

			Assert().AreEqual(memcmp(&index,&exp,sizeof(int)*3),0,L"Coord In Model Space Fail");
		}

	};

	
}
#endif