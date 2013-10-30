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
	Commentend out. Does not return a value
	For this application need pass by reference and should not use SDK specific Types...
	Flexibility needed if sensor changes... say using the Kinect instead

	PXCPoint3DF32 sf_model_builder::applyCoords(PXCPoint3DF32 pos3d)
	{
		//pos3d = ((pos3d.x - 1) * lengthx + (pos3d.y - 1) * lengthy + pos3d.y) + 1; 
	}

	/**
	Commentend out. Does not return a value
	For this application need pass by reference and should not use SDK specific Types...
	Flexibility needed if sensor changes... say using the Kinect instead
	PXCPoint3DF32 sf_model_builder::moveToOrigin(PXCFaceAnalysis::Landmark::LandmarkData ldata, PXCPoint3DF32 pos3d)
	{
		pos3d.x -= ldata.position.x;
		pos3d.y -= ldata.position.y;
		pos3d.z -= ldata.position.z;
	}
	*/
	/*
	pxcF32 * sf_model_builder::getTransformationMatrix(PXCFaceAnalysis::Landmark::PoseData pdata)
	{

		pxcF32 tx[3][3] = {{1,0,0},{0,cos(pdata.yaw),-sin(pdata.yaw)},{0,sin(pdata.yaw),cos(pdata.yaw)}};
		pxcF32 ty[3][3] = {{cos(pdata.pitch),0,sin(pdata.pitch)},{0,1,0},{-sin(pdata.pitch),0,cos(pdata.pitch)}};
		pxcF32 tz[3][3] = {{cos(pdata.roll),-sin(pdata.roll),0},{sin(pdata.roll),cos(pdata.roll),0},{0,0,1}};

		pxcF32 temp[3][3] = {{tx[1][1] * ty[1][1] + tx[1][2]*ty[2][1] + tx[1][3] * ty[3][1], tx[1][1] * ty[1][2] + tx[1][2]*ty[2][2] + tx[1][3] * ty[3][2], tx[1][1] * ty[1][3] + tx[1][2]*ty[2][3] + tx[1][3] * ty[3][3]},
						   {tx[2][1] * ty[1][1] + tx[2][2]*ty[2][1] + tx[2][3] * ty[3][1], tx[2][1] * ty[1][2] + tx[2][2]*ty[2][2] + tx[2][3] * ty[3][2], tx[2][1] * ty[1][3] + tx[2][2]*ty[2][3] + tx[2][3] * ty[3][3]},
						   {tx[3][1] * ty[1][1] + tx[3][2]*ty[2][1] + tx[3][3] * ty[3][1], tx[3][1] * ty[1][2] + tx[3][2]*ty[2][2] + tx[3][3] * ty[3][2], tx[3][1] * ty[1][3] + tx[3][2]*ty[2][3] + tx[3][3] * ty[3][3]}};


		pxcF32 tm[3][3] = {{temp[1][1] * tz[1][1] + temp[1][2]*tz[2][1] + temp[1][3] * tz[3][1], temp[1][1] * tz[1][2] + temp[1][2]*ty[2][2] + temp[1][3] * tz[3][2], temp[1][1] * tz[1][3] + temp[1][2]*tz[2][3] + temp[1][3] * tz[3][3]},
						   {temp[2][1] * tz[1][1] + temp[2][2]*tz[2][1] + temp[2][3] * tz[3][1], temp[2][1] * tz[1][2] + temp[2][2]*ty[2][2] + temp[2][3] * tz[3][2], temp[2][1] * tz[1][3] + temp[2][2]*tz[2][3] + temp[2][3] * tz[3][3]},
						   {temp[3][1] * tz[1][1] + temp[3][2]*tz[2][1] + temp[3][3] * tz[3][1], temp[3][1] * tz[1][2] + temp[3][2]*ty[2][2] + temp[3][3] * tz[3][2], temp[3][1] * tz[1][3] + temp[3][2]*tz[2][3] + temp[3][3] * tz[3][3]}};

		return *tm;
	}

	PXCPoint3DF32 sf_model_builder::applyTransform(PXCPoint3DF32 pos3d, pxcF32 tm[3][3])
	{
		pos3d.x = (pos3d.x * tm[1][1] + pos3d.y * tm[1][2] + pos3d.z * tm[1][3]);
		pos3d.y = (pos3d.x * tm[2][1] + pos3d.y * tm[2][2] + pos3d.z * tm[2][3]);
		pos3d.z = (pos3d.x * tm[3][1] + pos3d.y * tm[3][2] + pos3d.z * tm[3][3]);

		return pos3d;
	}

	PXCPoint3DF32 sf_model_builder::coordTransform(PXCPoint3DF32 pos3d)
	{
		pos3d.x = floor((pos3d.x - SF_DEFAULT_XMIN) / SF_DEFAULT_DELTAX);
		pos3d.y = floor((pos3d.y - SF_DEFAULT_YMIN) / SF_DEFAULT_DELTAY);
		pos3d.z = floor((pos3d.z - SF_DEFAULT_ZMIN) / SF_DEFAULT_DELTAZ);

		return pos3d;
	}

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