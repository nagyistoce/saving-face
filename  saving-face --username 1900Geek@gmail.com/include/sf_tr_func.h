#include "sf_defs.h"
#include "sf_model.h"


namespace SF
{
	//Pass in the nose coord, and the Yaw, Pitch, and Roll
	//The two peaces of info required to fully define the transform
	//Calculated once per frame
	SF_TR_MATRIX* calculateTRMatrix(const SF_R3_COORD &rwcReference, const SF_YPR &ypr);

	//So the Actual Transformation
	//Make as a single inline function call for simplicity, however
	//The transform functions themselves can/should be individual functions
	inline SF_MODEL_COORD3D* transformCoord(const SF_R3_COORD &realWorldCoord, const SF_TR_MATRIX *tr_matrix);
	
	//Transforms the Coord into indexed model coords
	//Returns null if outside model space.
	inline SF_MODEL_COORD3D_INDEX* coordInModelSpace(const SF_MODEL_COORD3D &md_Coord, const Model::Model_Info *model);

	//Apply the translation to a coord
	inline SF_R3_COORD translateCoord(const SF_R3_COORD &origCoord, SF_TR_MATRIX *tr_matrix);

	//Rotate a translated coord, must be done in that order.
	inline SF_MODEL_COORD3D* rotateCoord(const SF_R3_COORD &realWorldCoord, const SF_TR_MATRIX *tr_matrix);
}