#pragma once
#include "sf_defs.h"
#include "sf_model.h"
#include <iostream>

namespace SF
{
	//This classes responsibility, is to ensure proper instantiation and initialization of a model
	//And to apply coordinates to the model until X number of Frames, or told to stop.
	//It should then be able to rerun the data (From recorded video) used to create the model to give a proxy for a good score.
	//Need to add the ability to hold on to those scores in the model class.
	//This should call a sdk loop to accomplish this task.
	//In order to prevent unnecessary code replication, it should call a predefined function in the sf_sdk_session
	//class and pass in a recieving function as an argument, and an argument to record the video with a filename.

	
	class sf_model_builder
	{


	public:

		sf_model_builder(void);
		~sf_model_builder(void);

	};
}
