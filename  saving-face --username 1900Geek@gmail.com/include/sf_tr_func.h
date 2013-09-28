#include "sf_defs.h"
#include "sf_model.h"


namespace SF
{
	
	SF_TR_MATRIX calculateTRMatrix(const PXCPoint3DF32 rwcReference, const SF_YPR ypr);

	SF_MODEL_COORD3D transformCoord(const PXCPoint3DF32 realWorldCoord, const SF_TR_MATRIX);

	SF_STS coordInModelSpace(const SF_MODEL_COORD3D mdsCoord, const Model *model);

}