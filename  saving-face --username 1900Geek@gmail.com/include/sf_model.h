#pragma once
#include "sf_defs.h"
#include <fstream>

using namespace std;
namespace SF
{
	//TODO make the code const correct


	//Define Defaults
	//Tweak here to manipulate the default configuration
	//Will not affect previous instances
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
//Allows for unit testing of private datamembers
//Refactoring to use structs will make this (TODO)
//And a whole bunch of setters and getters unneccesary
//Not sure about viewing these structs in C#
//May need the getters and setters their, so best to keep them.
#ifdef _DEBUG
	public:
#else
	private:
#endif //_DEBUG
		
		//TODO make this a struct and return const version only
		SF_PUID puid;
		SF_NAME salutation, firstName, middleName, lastName, suffix;
		SF_EMAIL emailAddress;
		SF_GENDER gender;
		
		//TODO make this a struct and return const version only
		SF_MUID muid;
		SF_BOUND xMin, xMax, yMin, yMax, zMin, zMax;
		SF_DELTA deltaX, deltaY, deltaZ;
		SF_ARR_WIDTH xWidth, yWidth, zWidth;
		SF_ARR_OFFSET  xOffset, yOffset;
		SF_MODEL_ARR modelArr;
		
	
		//Creates a model with the default settings
		Model(void);//Should only be used for debug
#ifndef _DEBUG
	public:
#endif
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

		//Set the name of a model simple
		SF_STS setName(SF_NAME firstName, SF_NAME lastName);

		//Set the gender of a model
		//Only allow for male or female, for statistics purposes.
		//If release, include not_specified or other
		//Stores lowercase version only.
		SF_STS setGender(SF_GENDER);

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

		//Initialize a blank model array
		SF_STS initModelArray();

		//Gets the full name as a single string
		//Default name parts are set to ""
		SF_NAME getConcatenatedName();

		SF_NAME getSalutation();

		SF_NAME getFirstName();

		SF_NAME getMiddleName();

		SF_NAME getLastName();

		SF_NAME getSuffix();

		//Gets a full name with '_' concatenation instead of spaces
		SF_NAME getFileVersionName();

		//Returns lower-case only
		SF_GENDER getGender();

		SF_EMAIL getEmail();
	};
}

