#pragma once
#include "sf_defs.h"
#include <fstream>

using namespace std;
namespace SF
{
#define SF_DEFAULT_XMIN (-0.15f)
#define SF_DEFAULT_XMAX (0.15f)
#define SF_DEFAULT_YMIN (-0.15f)
#define SF_DEFAULT_YMAX (0.15f)
#define SF_DEFAULT_ZMIN (-0.05f)
#define SF_DEFAULT_ZMAX (0.45f)
#define SF_DEFAULT_DELTAX (0.0025f)
#define SF_DEFAULT_DELTAY (0.0025f)
#define SF_DEFAULT_DELTAZ (0.0025f)
	
	class Model
	{

	public:
		//For testing access to the constructor will remain public,
		//This should eventially be handled by the model db manager.
	
		SF_MUID muid;
		SF_PUID puid;
		SF_NAME salutation, firstName, middleName, lastName, suffix;
		SF_EMAIL emailAddress;
		SF_BOUND xMin, xMax, yMin, yMax, zMin, zMax;
		SF_DELTA deltaX, deltaY, deltaZ;
		SF_ARR_WIDTH xWidth, yWidth, zWidth;
		SF_ARR_OFFSET  xOffset, yOffset;
		SF_MODEL_ARR modelArr;

		//Creates a model with the default settings
		//Generic Model used only if loading from a file, or for troubleshooting.
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

		//Set the name of a model
		SF_STS setName(SF_NAME salutation, SF_NAME firstName, SF_NAME middleName, SF_NAME lastName, SF_NAME suffix);

		//Set the email address of a model
		SF_STS setEmail(SF_EMAIL emailAddress);

		//Sends the contents of a model to a file.
		SF_STS streamToFile(ofstream const *fileStream);

		//Loads the contents of a model to a file.
		SF_STS loadFromFile(ifstream const *fileStream);

		//Set the default parameters
		SF_STS setDefaultParameters();

		//Initialize a blank array
		SF_STS initModelArray();
	};
}

