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

		

		TEST_METHOD(testCoordInModelSpace)
		{
			SF::Model *model = new SF::Model();
			

			SF::SF_MODEL_COORD3D coord3d;
			SF::Model::Model_Info info = model->getModelInfo();

			coord3d.x = model->getModelInfo().xMin;
			coord3d.y = model->getModelInfo().yMin;
			coord3d.z = model->getModelInfo().zMin;

			//Commented out:  Unresolved External Symbol?
			//SF::SF_MODEL_COORD3D_INDEX *index = SF::coordInModelSpace(coord3d, &info);

			//if (index->x != 0 && index->y != 0 && index->z != 0)
			//{
			//	Assert().Fail();
			//}
		}

		TEST_METHOD(testCalculateTrMatrix)
		{
			
			PXCPoint3DF32 trv = {1,1,1};
			SF::SF_YPR ypr = {0,0,0};
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
			sprintf(str, "Translation Vector::\n %f, %f, %f\n", tm.trV.x,tm.trV.y,tm.trV.z);
			Logger::WriteMessage(str);
			
			sprintf(str, "Rotation Matrix Contains::\n %f, %f, %f\n%f, %f, %f\n%f, %f, %f", 
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

			//Add a test that calculates a rotation with a known output.
		}



	};
}