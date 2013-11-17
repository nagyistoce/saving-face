#pragma once
#include "sf_defs.h"
#include <fstream>

using namespace std;
namespace SF
{
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
	public:
		
		struct Person_Info
		{
			SF_PUID puid;
			SF_NAME salutation, firstName, middleName, lastName, suffix;
			SF_EMAIL emailAddress;
			SF_GENDER gender;
		};
		
		struct Model_Info
		{
			Person_Info *person_info;
			SF_MUID muid;
			SF_BOUND xMin, xMax, yMin, yMax, zMin, zMax;
			SF_DELTA deltaX, deltaY, deltaZ;
			SF_ARR_WIDTH xWidth, yWidth, zWidth;
			SF_ARR_OFFSET  xOffset, yOffset;
			SF_MODEL_ARR modelArr;
		};
		
	
		//Creates a model with the default settings
		//The reason there is no load from file constructor is
		//That it eliminates the need for exception handling on
		//Failed construction
		Model(void);//Should only be used for debug or load from file.


		Model(SF_NAME firstName, SF_NAME lastName, SF_GENDER gender, SF_EMAIL email = "");

		//Creates a model with the default settings
		//Adds Name
		//Generic Model
		Model(SF_NAME salutation, SF_NAME firstName, SF_NAME middleName, SF_NAME lastName, SF_NAME suffix, SF_GENDER gender, SF_EMAIL email = "");
		
		//Create a model with custom settings
		//Not needed if loading from a file
		Model(SF_NAME salutation, SF_NAME firstName, SF_NAME middleName, SF_NAME lastName, SF_NAME suffix, SF_GENDER gender, SF_EMAIL email,
			SF_BOUND xMin,SF_BOUND xMax,SF_BOUND yMin,SF_BOUND yMax,SF_BOUND zMin,
			SF_BOUND zMax,SF_DELTA deltaX,SF_DELTA deltaY,SF_DELTA deltaZ);


		//Destroys the model
		~Model(void);

		//Set the name of a model simple
		SF_STS Model::setName(SF_NAME firstName, SF_NAME lastName);

		//Set the gender of a model
		//Only allow for male or female, for statistics purposes.
		//If release, include not_specified or other
		//Stores lowercase version only.
		SF_STS setGender(SF_GENDER gender);

		//Set the name of a model
		SF_STS setName(SF_NAME salutation, SF_NAME firstName, SF_NAME middleName, SF_NAME lastName, SF_NAME suffix);

		//Set the email address of a model
		SF_STS setEmail(SF_EMAIL emailAddress);

		//Sends the contents of a model to a file.
		SF_STS streamToFile(ofstream *fileStream);

		//Loads the contents of a model to a file.
		SF_STS loadFromFile(ifstream *fileStream);

		//Set the default parameters
		SF_STS setDefaultParameters();

		SF_STS setParameters(SF_BOUND xMin,SF_BOUND xMax,SF_BOUND yMin,SF_BOUND yMax,SF_BOUND zMin,
			SF_BOUND zMax,SF_DELTA deltaX,SF_DELTA deltaY,SF_DELTA deltaZ);

		//Initialize a blank model array
		SF_STS initModelArray();

		//Gets the full name as a single string
		//Default name parts are set to ""
		SF_NAME getConcatenatedName();

		//Gets the salutation Mr. Mrs. Dr. etc...
		const SF_NAME getSalutation();

		//Gets the first name
		const SF_NAME getFirstName();

		//Gets the middle name
		const SF_NAME getMiddleName();

		//Gets the last name
		const SF_NAME getLastName();

		//Gets the suffix
		const SF_NAME getSuffix();

		//Gets a full name with '_' concatenation instead of spaces
		SF_NAME getFileVersionName();

		//Returns lower-case only
		const SF_GENDER getGender();

		//gets the email address
		const SF_EMAIL getEmail();

		//gets a referance to a read only version of model_info
		const Model_Info* getModelInfo();

		//gets a referance to a read only version of person_info
		const Person_Info* getPersonInfo();

		//Caller must check for null pointer
		const SF_MODEL_ARR getReadOnlyModelArr();

		//Caller must check for null pointer
		SF_MODEL_ARR getWritableModelArr();

		void setPersonUID(const SF_PUID puid);

		void setModelUID(const SF_MUID muid);

		SF_PUID getPersonUID();

		SF_MUID getModelUID();

	private:
		Model_Info model_info;
		Person_Info person_info;
		int arrLength;
	};
}

