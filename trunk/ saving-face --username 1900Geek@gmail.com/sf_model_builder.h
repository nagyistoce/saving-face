#pragma once
#include "sf_defs.h"

class sf_model_builder
{
public:

	//Transform a real world 3Dcoord into real world model space
	inline SF_F32 *CoordTransform(pxcF32 const *coord3D);


	sf_model_builder(void);
	~sf_model_builder(void);
};

