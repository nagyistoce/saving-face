#include "sf_model_builder.h"

namespace SF
{
	sf_model_builder::sf_model_builder(void)
	{
	}


	sf_model_builder::~sf_model_builder(void)
	{
	}

	/*

	void sf_model_builder::tempTestingModule()
	{
		//coordTransform TEST
		PXCPoint3DF32 temp;
		temp.x = SF_DEFAULT_XMIN;
		temp.y = SF_DEFAULT_YMIN;
		temp.z = SF_DEFAULT_ZMIN;

		temp = coordTransform(temp);

		if (temp.x == 0 && temp.y == 0 && temp.z == 0)
			std::printf("coordinate transform test 1 success\n");
		else
			std::printf("coordinate transform test 1 failed\n");
		//END coordTransform TEST

		//movePointsToOrigin TEST
		PXCFaceAnalysis::Landmark::LandmarkData ldata;
		ldata.position.x = 100;
		ldata.position.y = 100;
		ldata.position.z = 100;
		
		temp.x = 100;
		temp.y = 100;
		temp.z = 100;

		temp = moveToOrigin(ldata, temp);

		if (temp.x == 0 && temp.y == 0 && temp.z == 0)
			std::printf("coordinate transform test 1 success\n");
		else
			std::printf("coordinate transform test 1 failed\n");
		//END movePointsToOrigin TEST



		while(true){

		}
		
	}*/

}