#include "sf_defs.h"
#include "sf_model.h"


namespace SF
{
	//Pass in the nose coord, and the Yaw, Pitch, and Roll
	SF_TR_MATRIX* calculateTRMatrix(const SF_R3_COORD &rwcReference, const SF_YPR &ypr);

	//So the Actual Transformation
	SF_MODEL_COORD3D* transformCoord(const SF_R3_COORD &realWorldCoord, const SF_TR_MATRIX *tr_matrix);
	
	//Transforms the Coord into indexed model coords
	//Returns null if outside model space.
	SF_MODEL_COORD3D_INDEX* coordInModelSpace(const SF_MODEL_COORD3D &md_Coord, const Model::Model_Info *model);
}