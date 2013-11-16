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
			
			SF::translateCoord(out, origCoord, tr);

			Assert().AreEqual(memcmp(&(out),&(exp),sizeof(float)*3),0,L"Translation Vector Fail");
		}

		TEST_METHOD(testVectorRotation){
			SF::SF_MODEL_COORD3D out, exp;
			SF::SF_R3_COORD tr_coord3d;
			SF::SF_TR_MATRIX matrix;


			//I agree that this may be a valid test of the mathematics
			//However this is not a realistic test of the rotational qualities of the matrix.
			//The rotation matrix used is not composed of unit vectors,
			//representing the rotation about an arbitrary axis.
			//The transform is also not a scalar representation where |in| = |out| as would be expected,
			//and should be tested for.
			//Suggest using well known functions such as Sin(PI/4)... with expected outputs... and exceptable error
			//do to fp calculations... on the order of 10^-10 for our purposes (over kill I know. But any more suggest a serious
			//flaw in the code).
			//Better use a calculated tr matrix, with a YPR that is non zero, and not divisable by Pi/4.
			//So that we know that we are truly rotatating about an axis. And not simply doing matrix, mult.
			//which is tested elsewhere.

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

			SF::rotateCoord(out, tr_coord3d, matrix);

			Assert().AreEqual(memcmp(&out,&exp,sizeof(float)*3),0,L"Rotate Matrix Fail");

			Assert().Fail(L"Until Updated");
		}

		TEST_METHOD(testVectorTransform)
		{
			SF::SF_TR_MATRIX tr;
			SF::SF_R3_COORD origCoord;
			SF::SF_MODEL_COORD3D out, exp;

			origCoord.x = 10;
			origCoord.y = 15;
			origCoord.z = 20;

			tr.trV.x = 5;
			tr.trV.y = 10;
			tr.trV.z = 15;

			tr.rotMTX[0] = 3;
			tr.rotMTX[1] = 1;
			tr.rotMTX[2] = 3;
			tr.rotMTX[3] = 1;
			tr.rotMTX[4] = 3;
			tr.rotMTX[5] = 1;
			tr.rotMTX[6] = 3;
			tr.rotMTX[7] = 1;
			tr.rotMTX[8] = 3;

			exp.x = 35;
			exp.y = 25;
			exp.z = 35;
			
			SF::transformCoord(out, origCoord, tr);

			Assert().AreEqual(memcmp(&(out),&(exp),sizeof(float)*3),0,L"Transform Vector Fail");

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

			SF::MatrixMultiply1b3(out, tr_coord3d, matrix);

			sprintf(str, "Output Matrix Contains::\n%f, %f, %f", 
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

			Assert().AreEqual(memcmp(&out,&exp,sizeof(float)*3),0,L"3X3 Matrices Multiplication Fail");
		}


		TEST_METHOD(testCoordInModelSpace)
		{
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

			Assert().AreEqual(memcmp(&index,&exp,sizeof(float)*3),0,L"Coord In Model Space Fail");
		}

	};

	
}