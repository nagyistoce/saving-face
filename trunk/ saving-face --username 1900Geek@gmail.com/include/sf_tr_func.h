#include "sf_defs.h"
#include "sf_model.h"


namespace SF
{
	//Function Prototypes

	//Pass in the nose coord, and the Yaw, Pitch, and Roll
	//The two peaces of info required to fully define the transform
	//Calculated once per frame
	SF_TR_MATRIX * calculateTRMatrix(const SF_R3_COORD &rwcReference, const SF_YPR &ypr);

	//So the Actual Transformation
	//Make as a single inline function call for simplicity, however
	//The transform functions themselves can/should be individual functions
	inline SF_MODEL_COORD3D* transformCoord(const SF_R3_COORD &realWorldCoord, const SF_TR_MATRIX *tr_matrix);

	//So the Actual Transformation
	//Make as a single inline function call for simplicity, however
	//The transform functions themselves can/should be individual functions
	inline SF_MODEL_COORD3D* transformCoord(const SF_R3_COORD &realWorldCoord, const SF_TR_MATRIX *tr_matrix);




	//Implementation
	
	//Vars to include in the model builder class when made.
	//SF_MODEL_COORD3D *md_Coord;
	//SF_TR_MATRIX *tr_matrix;
	//SF_MODEL_COORD3D_INDEX *mdl_index_coord;

	
	SF_TR_MATRIX * calculateTRMatrix(const SF_R3_COORD &rwcReference, const SF_YPR &ypr)
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


	inline void transformCoord(const SF_R3_COORD &realWorldCoord, const SF_TR_MATRIX *tr_matrix)
	{
		
	}
	
	//Transforms the Coord into indexed model coords
	//Returns null if outside model space.
	inline void coordInModelSpace(SF_MODEL_COORD3D_INDEX &returnIndex, const SF_MODEL_COORD3D &md_Coord, const Model::Model_Info *model)
	{
		SF_MODEL_COORD3D_INDEX *returnIndex = new SF_MODEL_COORD3D_INDEX;
		returnIndex.x = floor((md_Coord.x - model->xMin) / model->deltaX);
		returnIndex.y = floor((md_Coord.y - model->yMin) / model->deltaY);
		returnIndex.z = floor((md_Coord.z - model->zMin) / model->deltaZ);
	}

	//Apply the translation to a coord
	inline SF_R3_COORD *translateCoord(SF_R3_COORD &model_Coord3d, const SF_R3_COORD &origCoord, SF_TR_MATRIX *tr_matrix){
		SF_R3_COORD model_Coord3d;
		model_Coord3d.x = origCoord.x - tr_matrix->trV.x;
		model_Coord3d.y = origCoord.y - tr_matrix->trV.y;
		model_Coord3d.z = origCoord.z - tr_matrix->trV.z;		
		return &model_Coord3d;
	}
	
	inline SF_MODEL_COORD3D *rotateCoord(SF_MODEL_COORD3D &model_r3_coord,const SF_R3_COORD &tr_Coord3d, const SF_TR_MATRIX *tr_matrix)
	{
		model_r3_coord.x = (tr_Coord3d.x * tr_matrix->rotMTX[0] + tr_Coord3d.y * tr_matrix->rotMTX[1] + tr_Coord3d.z * tr_matrix->rotMTX[2]);
		model_r3_coord.y = (tr_Coord3d.x * tr_matrix->rotMTX[3] + tr_Coord3d.y * tr_matrix->rotMTX[4] + tr_Coord3d.z * tr_matrix->rotMTX[5]);
		model_r3_coord.z = (tr_Coord3d.x * tr_matrix->rotMTX[6] + tr_Coord3d.y * tr_matrix->rotMTX[7] + tr_Coord3d.z * tr_matrix->rotMTX[8]);
		return &model_r3_coord;
	}
}