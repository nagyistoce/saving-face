#include "sf_defs.h"
//#include "sf_tr_func.h"
//#include <xnamath.h>


//Logic moved to header
namespace SF
{
	
	//Pass in the nose coord, and the Yaw, Pitch, and Roll
	SF_TR_MATRIX* calculateTRMatrix(const SF_R3_COORD &rwcReference, const SF_YPR &ypr)
	{
		//Note depending on the referance frame we made need to apply the inverse of ypr.

		SF_TR_MATRIX *tm = new SF_TR_MATRIX;

		tm->trV = rwcReference;

		SF_SCALAR tx[9] = {1.f,0.f,0.f,0.f, cos(ypr.yaw),-sin(ypr.yaw),0.f,sin(ypr.yaw),cos(ypr.yaw)};
		SF_SCALAR ty[9] = {cos(ypr.pitch),0.f,sin(ypr.pitch),0.f,1.f,0.f,-sin(ypr.pitch),0.f,cos(ypr.pitch)};
		SF_SCALAR tz[9] = {cos(ypr.roll),-sin(ypr.roll),0.f,sin(ypr.roll),cos(ypr.roll),0.f,0.f,0.f,1.f};

		//Updated tx[3] * ty[3] to read tx[4]*ty[4]... Great job though andy this must have been hard to keep track of.
		SF_SCALAR temp[9] = {tx[0] * ty[0] + tx[1]*ty[3] + tx[2] * ty[6], tx[0] * ty[1] + tx[1]*ty[4] + tx[2] * ty[7], tx[0] * ty[2] + tx[1]*ty[5] + tx[2] * ty[8],
						     tx[3] * ty[0] + tx[4]*ty[3] + tx[5] * ty[6], tx[3] * ty[1] + tx[4]*ty[4] + tx[5] * ty[7], tx[3] * ty[2] + tx[4]*ty[5] + tx[5] * ty[8],
						     tx[6] * ty[0] + tx[7]*ty[3] + tx[8] * ty[6], tx[6] * ty[1] + tx[7]*ty[4] + tx[8] * ty[7], tx[6] * ty[2] + tx[7]*ty[5] + tx[8] * ty[8]};

		SF_SCALAR tmMatrix[9] ={temp[0] * tz[0] + temp[1]*tz[3] + temp[2] * tz[6], temp[0] * tz[1] + temp[1]*tz[4] + temp[2] * tz[7], temp[0] * tz[2] + temp[1]*tz[5] + temp[2] * tz[8],
								temp[3] * tz[0] + temp[4]*tz[3] + temp[5] * tz[6], temp[3] * tz[1] + temp[4]*tz[4] + temp[5] * tz[7], temp[3] * tz[2] + temp[4]*tz[5] + temp[5] * tz[8],
								temp[6] * tz[0] + temp[7]*tz[3] + temp[8] * tz[6], temp[6] * tz[1] + temp[7]*tz[4] + temp[8] * tz[7], temp[6] * tz[2] + temp[7]*tz[5] + temp[8] * tz[8]};
		

		//SF_SCALAR *temp = MatrixMultiply3b3(*tx, *tz); 
		memcpy(tm->rotMTX, tmMatrix, sizeof(float)*9);

		return tm;
	}


	inline SF_SCALAR *MatrixMultiply1b3(SF_SCALAR &MTX1b3, SF_SCALAR &MTX3b3)
	{
		return 0;
	}

	inline SF_SCALAR *MatrixMultiply3b3(SF_SCALAR &MTX3b31, SF_SCALAR &MTX3b32)
	{
		//Couldn't get this to work for the life of me.
		/*SF_SCALAR *temp[9] = {MTX3b31[0] * MTX3b32[0] + MTX3b31[1]*MTX3b32[3] + MTX3b31[2] * MTX3b32[6], MTX3b31[0] * MTX3b32[1] + MTX3b31[1]*MTX3b32[4] + MTX3b31[2] * MTX3b32[7], MTX3b31[0] * MTX3b32[2] + MTX3b31[1]*MTX3b32[5] + MTX3b31[2] * MTX3b32[8],
				MTX3b31[3] * MTX3b32[0] + MTX3b31[4]*MTX3b32[3] + MTX3b31[5] * MTX3b32[6], MTX3b31[3] * MTX3b32[1] + MTX3b31[4]*MTX3b32[4] + MTX3b31[5] * MTX3b32[7], MTX3b31[3] * MTX3b32[2] + MTX3b31[4]*MTX3b32[5] + MTX3b31[5] * MTX3b32[8],
			    MTX3b31[6] * MTX3b32[0] + MTX3b31[7]*MTX3b32[3] + MTX3b31[8] * MTX3b32[6], MTX3b31[6] * MTX3b32[1] + MTX3b31[7]*MTX3b32[4] + MTX3b31[8] * MTX3b32[7], MTX3b31[6] * MTX3b32[2] + MTX3b31[7]*MTX3b32[5] + MTX3b31[8] * MTX3b32[8]};
				*/
		return NULL;
	}

	
	
	//Transforms the Coord into indexed model coords
	//Returns null if outside model space.
	inline SF_MODEL_COORD3D_INDEX* coordInModelSpace(const SF_MODEL_COORD3D &md_Coord, const Model::Model_Info *model)
	{
		SF_MODEL_COORD3D_INDEX *returnIndex = new SF_MODEL_COORD3D_INDEX;

		returnIndex->x = floor((md_Coord.x - model->xMin) / model->deltaX);
		returnIndex->y = floor((md_Coord.y - model->yMin) / model->deltaY);
		returnIndex->z = floor((md_Coord.z - model->zMin) / model->deltaZ);

		//TODO check if outside model space.
		return returnIndex;
	}
}