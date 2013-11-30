#include "sf_tr_test.h"
#include "sf_tr_func.h"
//Which
namespace SFTEST
{
	void calculateTRMatrix(SF::SF_TR_MATRIX &tm, SF::SF_R3_COORD &rwcReference, const SF::SF_YPR &ypr)
	{
		SF::calculateTRMatrix(tm,  rwcReference, ypr);
	}

	void translateCoord(SF::SF_R3_COORD &model_Coord3d, const SF::SF_R3_COORD &origCoord,const SF::SF_TR_MATRIX &tr_matrix)
	{
		SF::translateCoord(model_Coord3d, origCoord, tr_matrix);
	}
	void rotateCoord(SF::SF_MODEL_COORD3D &model_r3_coord,const SF::SF_R3_COORD &tr_Coord3d, const SF::SF_TR_MATRIX &tr_matrix)
	{
		SF::rotateCoord(model_r3_coord,tr_Coord3d,tr_matrix);
	}
	void transformCoord(SF::SF_MODEL_COORD3D &mdl_coord, const SF::SF_R3_COORD &realWorldCoord, const SF::SF_TR_MATRIX &tr_matrix)
	{
		SF::transformCoord(mdl_coord,realWorldCoord,tr_matrix);
	}
	void coordInModelSpace(SF::SF_MODEL_COORD3D_INDEX &returnIndexed, const SF::SF_MODEL_COORD3D &md_Coord, const SF::Model::Model_Info *model)
	{
		SF::coordInModelSpace(returnIndexed,md_Coord,model);
	}
	void MatrixMultiply3b3(SF::SF_SCALAR* out, const SF::SF_SCALAR* in1,const SF::SF_SCALAR* in2)
	{
		SF::MatrixMultiply3b3(out,in1,in2);
	}
	void MatrixMultiply1b3(SF::SF_MODEL_COORD3D &model_r3_coord,const SF::SF_R3_COORD &tr_Coord3d, const SF::SF_TR_MATRIX &tr_matrix)
	{
		SF::MatrixMultiply1b3(model_r3_coord,tr_Coord3d,tr_matrix);
	}
}