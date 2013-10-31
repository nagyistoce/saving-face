#include "sf_tr_func.h"
//#include <xnamath.h>

namespace SF
{
	
	//Pass in the nose coord, and the Yaw, Pitch, and Roll
	SF_TR_MATRIX* calculateTRMatrix(const SF_R3_COORD &rwcReference, const SF_YPR &ypr)
	{

		//Note depending on the referance frame we made need to apply the inverse of ypr.

		SF_TR_MATRIX *tm = new SF_TR_MATRIX;

		tm->trV = rwcReference;

		SF_SCALAR tx[9] = {1.f,0.f,0.f,0.f, cos(ypr.yaw),-sin(ypr.yaw),0.f,sin(ypr.yaw),cos(ypr.yaw)};
		SF_SCALAR ty[9] = {cos(ypr.pitch),0,sin(ypr.pitch),0,1,0,-sin(ypr.pitch),0,cos(ypr.pitch)};
		SF_SCALAR tz[9] = {cos(ypr.roll),-sin(ypr.roll),0,sin(ypr.roll),cos(ypr.roll),0,0,0,1};

		//Updated tx[3] * ty[3] to read tx[4]*ty[4]... Great job though andy this must have been hard to keep track of.
		SF_SCALAR temp[9] = {tx[0] * ty[0] + tx[1]*ty[3] + tx[2] * ty[6], tx[0] * ty[1] + tx[1]*ty[4] + tx[2] * ty[7], tx[0] * ty[2] + tx[1]*ty[5] + tx[2] * ty[8],
						     tx[3] * ty[0] + tx[4]*ty[3] + tx[5] * ty[6], tx[3] * ty[1] + tx[4]*ty[4] + tx[5] * ty[7], tx[3] * ty[2] + tx[4]*ty[5] + tx[5] * ty[8],
						     tx[6] * ty[0] + tx[7]*ty[3] + tx[8] * ty[6], tx[6] * ty[1] + tx[7]*ty[4] + tx[8] * ty[7], tx[6] * ty[2] + tx[7]*ty[5] + tx[8] * ty[8]};

		SF_SCALAR tmMatrix[9] ={temp[0] * tz[0] + temp[1]*tz[3] + temp[2] * tz[6], temp[0] * tz[1] + temp[1]*tz[4] + temp[2] * tz[7], temp[0] * tz[2] + temp[1]*tz[5] + temp[2] * tz[8],
								temp[3] * tz[0] + temp[4]*tz[3] + temp[5] * tz[6], temp[3] * tz[1] + temp[4]*tz[4] + temp[5] * tz[7], temp[3] * tz[2] + temp[4]*tz[5] + temp[5] * tz[8],
								temp[6] * tz[0] + temp[7]*tz[3] + temp[8] * tz[6], temp[6] * tz[1] + temp[7]*tz[4] + temp[8] * tz[7], temp[6] * tz[2] + temp[7]*tz[5] + temp[8] * tz[8]};


		memcpy(tm->rotMTX, tmMatrix, sizeof(float)*9);

		return tm;
	}

	inline SF_SCALAR *MatrixMultiply1b3(SF_SCALAR &MTX1b3, SF_SCALAR &MTX3b3)
	{

		return 0;
	}



	//So the Actual Transformation
	inline SF_MODEL_COORD3D* transformCoord(const SF_R3_COORD &realWorldCoord, const SF_TR_MATRIX *tr_matrix)
	{
		return NULL;
	}
	
	//Transforms the Coord into indexed model coords
	//Returns null if outside model space.
	inline SF_MODEL_COORD3D_INDEX* coordInModelSpace(const SF_MODEL_COORD3D &md_Coord, const Model::Model_Info *model)
	{
		return NULL;
	}
}