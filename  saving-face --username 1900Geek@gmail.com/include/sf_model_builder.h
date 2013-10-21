#pragma once
#include "sf_defs.h"
#include "pxcface.h"
#include "sf_model.h"
#include <iostream>

namespace SF
{
	//Ideally only one instance should be needed.
	class sf_model_builder
	{

	private:
		
		double xind;
		double yind;
		double zind;
		double lengthx;
		double lengthy;

	public:

		sf_model_builder(void);
		~sf_model_builder(void);

		PXCPoint3DF32 movePointsToOrigin(PXCFaceAnalysis::Landmark::LandmarkData ldata, PXCPoint3DF32 pos3d); //Center the model to the tip of the nose
		PXCPoint3DF32 coordTransform(PXCPoint3DF32 pos3d);
		void tempTestingModule();

		//Not finished
		pxcF32 * getTransform(PXCFaceAnalysis::Landmark::PoseData pdata); //Rotate around x,y,z axis, based on yaw,pitch, and roll.
		void applyTransform(PXCPoint3DF32 pos3d, pxcF32 tm[3][3]);
		PXCPoint3DF32 applyCoords(PXCPoint3DF32 pos3d);//Figure out what the arguments are.

	};
}
