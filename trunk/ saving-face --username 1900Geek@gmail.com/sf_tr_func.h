#include "sf_defs.h"
#include "sf_model.h"


namespace SF
{
	
	//This Function will Ideally have its inputs constructed by the SDK
	SF_TR_MATRIX calculateTRMatrix(const PXCPoint3DF32 rwcReference, const SF_YPR ypr);

	//Take a Raw 3D Coord and put orient it, return its Model space address.
	SF_MODEL_COORD3D transformCoord(const PXCPoint3DF32 realWorldCoord, const SF_TR_MATRIX);

	//Check to make sure a coord is within the bounds of model space
	SF_STS coordInModelSpace(const SF_MODEL_COORD3D mdsCoord, const Model *model);

}