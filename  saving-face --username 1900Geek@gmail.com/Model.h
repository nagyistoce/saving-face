#pragma once
#include "sf_defs.h"
#include <fstream>

namespace SF
{
	class Model
	{
	public:
		//This is being made a class instead of a struct to be more consistent with the OOP paradigm
		//Vars are public purely for speed of access
	
		SF_NAME salutation, firstName, lastName, suffix;
		SF_EMAIL email_address;
		SF_BOUND xMin, xMax, yMin, yMax, zMin, zMax;
		SF_DELTA deltaX, deltaY, deltaZ;
		SF_ARR_WIDTH xWidth, yWidth, zWidth;
		SF_ARR_OFFSET  xOffset, yOffset;

		//Creates a model with the default settings
		//Generic Model or used if loading from a file.
		Model(void);

		//Creates a model with the default settings
		//Adds Name and email to the model
		//Generic Model
		Model(SF_NAME salutation, SF_NAME firstName, SF_NAME middleName, SF_NAME lastName, SF_NAME suffix);
		
		//Create a model with custom settings
		//Not needed if loading from a file
		Model(SF_NAME salutation, SF_NAME firstName, SF_NAME middleName, SF_NAME lastName, SF_NAME suffix,
			SF_BOUND xMin,SF_BOUND xMax,SF_BOUND yMin,SF_BOUND yMax,SF_BOUND zMin,
			SF_BOUND zMax,SF_DELTA deltaX,SF_DELTA deltaY,SF_DELTA deltaZ);

		//Destroys the model
		~Model(void);

		//Sends the contents of a model to a file.
		SF_STS streamToFile(std::ofstream const *fileStream);

		//Loads the contents of a model to a file.
		SF_STS LoadFromFile(std::ifstream const *fileStream);
	};
}

