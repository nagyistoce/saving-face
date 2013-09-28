#pragma once
#include "sf_defs.h"

namespace SF
{
	//Ideally only one instance should be needed.
	class sf_model_builder
	{
	public:

		SF_STS applyCoords();//Figure out what the arguments are.

		sf_model_builder(void);
		~sf_model_builder(void);
	};
}
