#include "sf_defs.h"
#include "sf_model.h"


namespace SF
{
	//Todo refacator to use XNAMath.h, Allows for SIMD single cycle matrix operations
	//using 128 bit registers.

	//Function Prototypes

	//Pass in the nose coord, and the Yaw, Pitch, and Roll
	//The two peaces of info required to fully define the transform
	//Calculated once per frame
	void calculateTRMatrix(SF_TR_MATRIX &tm, SF_R3_COORD &rwcReference, const SF_YPR &ypr);

	//Apply linear translation to a vector
	inline void translateCoord(SF_R3_COORD &model_Coord3d, const SF_R3_COORD &origCoord,const SF_TR_MATRIX &tr_matrix);
	
	//Apply rotational transform to a vector.
	inline void rotateCoord(SF_MODEL_COORD3D &model_r3_coord,const SF_R3_COORD &tr_Coord3d, const SF_TR_MATRIX &tr_matrix);

	//So the Actual Transformation
	//Make as a single inline function call for simplicity, however
	//The transform functions themselves can/should be individual functions
	inline void transformCoord(SF_MODEL_COORD3D &mdl_coord, const SF_R3_COORD &realWorldCoord, const SF_TR_MATRIX &tr_matrix);

	//Transforms the Coord into indexed model coords
	inline void coordInModelSpace(SF_MODEL_COORD3D_INDEX &returnIndexed, const SF_MODEL_COORD3D &md_Coord, const Model::Model_Info *model);

		




	//Implementation
	
	//Vars to include in the model builder class when made.
	//SF_MODEL_COORD3D *md_Coord;
	//SF_TR_MATRIX *tr_matrix;
	//SF_MODEL_COORD3D_INDEX *mdl_index_coord;

	
	void calculateTRMatrix(SF_TR_MATRIX &tm, SF_R3_COORD &rwcReference, const SF_YPR &ypr)
	{
		//Note depending on the referance frame we made need to apply the inverse of ypr.
		tm.trV = rwcReference;

		SF_SCALAR tx[9] = {1.f,0.f,0.f,0.f, cos(ypr.yaw),-sin(ypr.yaw),0.f,sin(ypr.yaw),cos(ypr.yaw)};
		SF_SCALAR ty[9] = {cos(ypr.pitch),0.f,sin(ypr.pitch),0.f,1.f,0.f,-sin(ypr.pitch),0.f,cos(ypr.pitch)};
		SF_SCALAR tz[9] = {cos(ypr.roll),-sin(ypr.roll),0.f,sin(ypr.roll),cos(ypr.roll),0.f,0.f,0.f,1.f};

		SF_SCALAR temp[9] = {tx[0] * ty[0] + tx[1]*ty[3] + tx[2] * ty[6], tx[0] * ty[1] + tx[1]*ty[4] + tx[2] * ty[7], tx[0] * ty[2] + tx[1]*ty[5] + tx[2] * ty[8],
						     tx[3] * ty[0] + tx[4]*ty[3] + tx[5] * ty[6], tx[3] * ty[1] + tx[4]*ty[4] + tx[5] * ty[7], tx[3] * ty[2] + tx[4]*ty[5] + tx[5] * ty[8],
						     tx[6] * ty[0] + tx[7]*ty[3] + tx[8] * ty[6], tx[6] * ty[1] + tx[7]*ty[4] + tx[8] * ty[7], tx[6] * ty[2] + tx[7]*ty[5] + tx[8] * ty[8]};

		SF_SCALAR tmMatrix[9] ={temp[0] * tz[0] + temp[1]*tz[3] + temp[2] * tz[6], temp[0] * tz[1] + temp[1]*tz[4] + temp[2] * tz[7], temp[0] * tz[2] + temp[1]*tz[5] + temp[2] * tz[8],
								temp[3] * tz[0] + temp[4]*tz[3] + temp[5] * tz[6], temp[3] * tz[1] + temp[4]*tz[4] + temp[5] * tz[7], temp[3] * tz[2] + temp[4]*tz[5] + temp[5] * tz[8],
								temp[6] * tz[0] + temp[7]*tz[3] + temp[8] * tz[6], temp[6] * tz[1] + temp[7]*tz[4] + temp[8] * tz[7], temp[6] * tz[2] + temp[7]*tz[5] + temp[8] * tz[8]};
		
		memcpy(tm.rotMTX, tmMatrix, sizeof(float)*9);
	}


	inline void transformCoord(SF_MODEL_COORD3D &mdl_coord, const SF_R3_COORD &realWorldCoord, const SF_TR_MATRIX &tr_matrix){
		SF_R3_COORD r3_Coord;
		translateCoord(r3_Coord, realWorldCoord, tr_matrix);
		rotateCoord(mdl_coord, r3_Coord, tr_matrix);
	}
	


	inline void coordInModelSpace(SF_MODEL_COORD3D_INDEX &returnIndexed, const SF_MODEL_COORD3D &md_Coord, const Model::Model_Info *model){
		SF_MODEL_COORD3D_INDEX *returnIndex = new SF_MODEL_COORD3D_INDEX;
		returnIndexed.x = floor((md_Coord.x - model->xMin) / model->deltaX);
		returnIndexed.y = floor((md_Coord.y - model->yMin) / model->deltaY);
		returnIndexed.z = floor((md_Coord.z - model->zMin) / model->deltaZ);
	}


	inline void translateCoord(SF_R3_COORD &model_Coord3d, const SF_R3_COORD &origCoord,const SF_TR_MATRIX &tr_matrix){
		model_Coord3d.x = origCoord.x - tr_matrix.trV.x;
		model_Coord3d.y = origCoord.y - tr_matrix.trV.y;
		model_Coord3d.z = origCoord.z - tr_matrix.trV.z;		
	}
	
	inline void rotateCoord(SF_MODEL_COORD3D &model_r3_coord,const SF_R3_COORD &tr_Coord3d, const SF_TR_MATRIX &tr_matrix)
	{
		model_r3_coord.x = (tr_Coord3d.x * tr_matrix.rotMTX[0] + tr_Coord3d.y * tr_matrix.rotMTX[1] + tr_Coord3d.z * tr_matrix.rotMTX[2]);
		model_r3_coord.y = (tr_Coord3d.x * tr_matrix.rotMTX[3] + tr_Coord3d.y * tr_matrix.rotMTX[4] + tr_Coord3d.z * tr_matrix.rotMTX[5]);
		model_r3_coord.z = (tr_Coord3d.x * tr_matrix.rotMTX[6] + tr_Coord3d.y * tr_matrix.rotMTX[7] + tr_Coord3d.z * tr_matrix.rotMTX[8]);
	}


	//TODO
	inline SF_SCALAR *MatrixMultiply1b3(SF_SCALAR &MTX1b3, SF_SCALAR &MTX3b3)
	{
		return 0;
	}

	//TODO
	inline void MatrixMultiply3b3(SF_SCALAR* out, const SF_SCALAR* in1,const SF_SCALAR* in2)
	{
		out[0] = in1[0] * in2[0] + in1[1]*in2[3] + in1[2] * in2[6];
		out[1] = in1[0] * in2[1] + in1[1]*in2[4] + in1[2] * in2[7];
		out[2] = in1[0] * in2[2] + in1[1]*in2[5] + in1[2] * in2[8];
		out[3] = in1[3] * in2[0] + in1[4]*in2[3] + in1[5] * in2[6];
		out[4] = in1[3] * in2[1] + in1[4]*in2[4] + in1[5] * in2[7];
		out[5] = in1[3] * in2[2] + in1[4]*in2[5] + in1[5] * in2[8];
		out[6] = in1[6] * in2[0] + in1[7]*in2[3] + in1[8] * in2[6];
		out[7] = in1[6] * in2[1] + in1[7]*in2[4] + in1[8] * in2[7];
		out[8] = in1[6] * in2[2] + in1[7]*in2[5] + in1[8] * in2[8];
	}
}