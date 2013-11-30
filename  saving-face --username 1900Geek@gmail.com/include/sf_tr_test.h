#pragma once
#ifndef _SF_TR_TEST
#define _SF_TR_TEST
#include "sf_defs.h"
#include "sf_model.h"
//Which

namespace SFTEST
{
	void calculateTRMatrix(SF::SF_TR_MATRIX &tm, SF::SF_R3_COORD &rwcReference, const SF::SF_YPR &ypr);

	void translateCoord(SF::SF_R3_COORD &model_Coord3d, const SF::SF_R3_COORD &origCoord,const SF::SF_TR_MATRIX &tr_matrix);
	
	void rotateCoord(SF::SF_MODEL_COORD3D &model_r3_coord,const SF::SF_R3_COORD &tr_Coord3d, const SF::SF_TR_MATRIX &tr_matrix);

	void transformCoord(SF::SF_MODEL_COORD3D &mdl_coord, const SF::SF_R3_COORD &realWorldCoord, const SF::SF_TR_MATRIX &tr_matrix);

	void coordInModelSpace(SF::SF_MODEL_COORD3D_INDEX &returnIndexed, const SF::SF_MODEL_COORD3D &md_Coord, const SF::Model::Model_Info *model);

	void MatrixMultiply3b3(SF::SF_SCALAR* out, const SF::SF_SCALAR* in1,const SF::SF_SCALAR* in2);

	void MatrixMultiply1b3(SF::SF_MODEL_COORD3D &model_r3_coord,const SF::SF_R3_COORD &tr_Coord3d, const SF::SF_TR_MATRIX &tr_matrix);

}

#endif



