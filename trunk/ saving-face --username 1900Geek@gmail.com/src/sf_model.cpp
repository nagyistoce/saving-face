#include "sf_model.h"

/** The model class todo list
*   Implement error checking on Model Arr Params
*   Implement Save to file
*   Implement Read from file
*/


namespace SF
{
	Model::Model(void)
	{
		model_info.modelArr = 0;
		setDefaultParameters();
	}

	Model::Model(SF_NAME firstName, SF_NAME lastName,SF_GENDER gender, SF_EMAIL email)
	{
		model_info.modelArr = 0;
		setName(firstName,lastName);
		setEmail(email);
		setGender(gender);
		setDefaultParameters();
	}

	Model::Model(SF_NAME salutation, SF_NAME firstName, SF_NAME middleName, SF_NAME lastName, SF_NAME suffix,SF_GENDER gender,  SF_EMAIL email)
	{
		model_info.modelArr = 0;
		setName(salutation,firstName,middleName,lastName,suffix);
		setEmail(email);
		setGender(gender);
		setDefaultParameters();
	}

	Model::Model(SF_NAME salutation, SF_NAME firstName, SF_NAME middleName, SF_NAME lastName, SF_NAME suffix,SF_GENDER gender, SF_EMAIL email,
			SF_BOUND xMin,SF_BOUND xMax,SF_BOUND yMin,SF_BOUND yMax,SF_BOUND zMin,
			SF_BOUND zMax,SF_DELTA deltaX,SF_DELTA deltaY,SF_DELTA deltaZ)
	{
		model_info.modelArr = 0;
		setName(salutation,firstName,middleName,lastName,suffix);
		setEmail(email);
		setGender(gender);
		setParameters( xMin, xMax, yMin, yMax, zMin, zMax, deltaX, deltaY, deltaZ);
	}


	SF_STS Model::setName(SF_NAME salutation, SF_NAME firstName, SF_NAME middleName, SF_NAME lastName, SF_NAME suffix)
	{
		this->person_info.salutation = salutation;
		this->person_info.firstName = firstName;
		this->person_info.middleName = middleName;
		this->person_info.lastName = lastName;
		this->person_info.suffix = suffix;
		return SF_STS_OK;
	}

	SF_STS Model::setName(SF_NAME firstName, SF_NAME lastName)
	{
		this->person_info.firstName = firstName;
		this->person_info.lastName = lastName;
		return SF_STS_OK;
	}

	SF_STS Model::setDefaultParameters()
	{
		this->arrLength = -1;
		this->model_info.xMin = SF_DEFAULT_XMIN;
		this->model_info.yMin = SF_DEFAULT_YMIN;
		this->model_info.zMin = SF_DEFAULT_ZMIN;
		this->model_info.xMax = SF_DEFAULT_XMAX;
		this->model_info.yMax = SF_DEFAULT_YMAX;
		this->model_info.zMax = SF_DEFAULT_ZMAX;
		this->model_info.deltaX = SF_DEFAULT_DELTAX;
		this->model_info.deltaY = SF_DEFAULT_DELTAY;
		this->model_info.deltaZ = SF_DEFAULT_DELTAZ;
		this->model_info.xWidth = (SF_ARR_WIDTH)(((this->model_info.xMax - this->model_info.xMin)) / this->model_info.deltaX);
		//Potential bug if value is not a perfect integer
		//for now assume it is. 
		//But will likely fail on Apply coord in integration testing if not.
		this->model_info.yWidth = (SF_ARR_WIDTH)((this->model_info.yMax - this->model_info.yMin) / this->model_info.deltaY);
		this->model_info.zWidth = (SF_ARR_WIDTH)((this->model_info.zMax - this->model_info.zMin) / this->model_info.deltaZ);
		this->model_info.xOffset =(this->model_info.yWidth * this->model_info.zWidth);
		this->model_info.yOffset = this->model_info.zWidth;
		return SF_STS_OK;
	}

	SF_STS Model::setParameters(SF_BOUND xMin,SF_BOUND xMax,SF_BOUND yMin,SF_BOUND yMax,SF_BOUND zMin,
			SF_BOUND zMax,SF_DELTA deltaX,SF_DELTA deltaY,SF_DELTA deltaZ)
	{
		//TODO this version requires error checking. Can easily input a bogus parameter at
		//run time which will cause a crash.
		this->arrLength = -1;
		this->model_info.xMin = xMin;
		this->model_info.yMin = yMin;
		this->model_info.zMin = zMin;
		this->model_info.xMax = xMax;
		this->model_info.yMax = yMax;
		this->model_info.zMax = zMax;
		this->model_info.deltaX = deltaX;
		this->model_info.deltaY = deltaY;
		this->model_info.deltaZ = deltaZ;
		this->model_info.xWidth = (SF_ARR_WIDTH)(((this->model_info.xMax - this->model_info.xMin)) / this->model_info.deltaX);
		//Potential bug if value is not a perfect integer
		//for now assume it is. 
		//But will likely fail on Apply coord in integration testing if not.
		this->model_info.yWidth = (SF_ARR_WIDTH)((this->model_info.yMax - this->model_info.yMin) / this->model_info.deltaY);
		this->model_info.zWidth = (SF_ARR_WIDTH)((this->model_info.zMax - this->model_info.zMin) / this->model_info.deltaZ);
		this->model_info.xOffset =(this->model_info.yWidth * this->model_info.zWidth);
		this->model_info.yOffset = this->model_info.zWidth;
		return SF_STS_OK;
	}

	SF_STS Model::initModelArray()
	{
		if(this->model_info.modelArr){
			delete[] this->model_info.modelArr;
			this->model_info.modelArr = 0;
		}
		this->model_info.modelArr = new SF_MODEL_UNIT[this->model_info.xWidth * this->model_info.yWidth * this->model_info.zWidth];
		//Set model array to zero
		memset(this->model_info.modelArr,0,this->model_info.xWidth * this->model_info.yWidth * this->model_info.zWidth);
		if(this->model_info.modelArr){
			arrLength = this->model_info.xWidth * this->model_info.yWidth * this->model_info.zWidth;
			return SF_STS_OK;
		}
		//Insert Seperate Fail Condition For Debug and Release
		else
		{
			arrLength = -1;
			return SF_STS_MEM_ALLOC_FAIL;
		}
	}
	
	SF_STS Model::setEmail(SF_EMAIL emailAddress)
	{
		this->person_info.emailAddress = emailAddress;
		return SF_STS_OK;
	}

	SF_STS Model::streamToFile(ofstream *fileStream)
	{

		//The plus one is for the null terminating character
		char str[1028];
		sprintf_s(str,500, "%d&%s&%s&%s&%s&%s&%s&%s&%f&%f&%f&%d&%d&%f&%f&%f&%d&%d&%f&%f&%f&%d&%d", 
			person_info.puid,
			getGender().c_str(),
			person_info.salutation.c_str(),
			person_info.firstName.c_str(),
			person_info.middleName.c_str(),
			person_info.lastName.c_str(),
			person_info.suffix.c_str(),
			person_info.emailAddress.c_str(),

			model_info.deltaX,
			model_info.xMax,
			model_info.xMin,
			model_info.xOffset,
			model_info.xWidth,

			model_info.deltaY,
			model_info.yMax,
			model_info.yMin,
			model_info.yOffset,
			model_info.yWidth,

			model_info.deltaZ,
			model_info.zMax,
			model_info.zMin,
			model_info.zWidth,
			model_info.muid
			);
		fileStream->write(str, strlen(str)+1);
		fileStream->write(model_info.modelArr,arrLength);
		//TODO put in some checks to make sure the array has been initialized.
		return SF_STS_OK;
	}

	SF_STS Model::loadFromFile(ifstream *fileStream)
	{
		char in[1028];
		*fileStream >> in;
		char *next_token = NULL;
		person_info.puid = atol(strtok_s(in,"&",&next_token));
		setGender(strtok_s(NULL, "&",&next_token));
		person_info.salutation = strtok_s(NULL, "&",&next_token);
		person_info.firstName = strtok_s(NULL, "&",&next_token);
		person_info.middleName = strtok_s(NULL, "&",&next_token);
		person_info.lastName = strtok_s(NULL, "&",&next_token);
		person_info.suffix = strtok_s(NULL, "&",&next_token);
		person_info.emailAddress = strtok_s(NULL, "&",&next_token);
		
		model_info.deltaX = atof(strtok_s(NULL,"&",&next_token));
		model_info.xMax = atof(strtok_s(NULL,"&",&next_token));
		model_info.xMin = atof(strtok_s(NULL,"&",&next_token));
		model_info.xOffset = atoi(strtok_s(NULL,"&",&next_token));
		model_info.xWidth = atoi(strtok_s(NULL,"&",&next_token));

		model_info.deltaY = atof(strtok_s(NULL,"&",&next_token));
		model_info.yMax = atof(strtok_s(NULL,"&",&next_token));
		model_info.yMin = atof(strtok_s(NULL,"&",&next_token));
		model_info.yOffset = atoi(strtok_s(NULL,"&",&next_token));
		model_info.yWidth = atoi(strtok_s(NULL,"&",&next_token));

		model_info.deltaZ = atof(strtok_s(NULL,"&",&next_token));
		model_info.zMax = atof(strtok_s(NULL,"&",&next_token));
		model_info.zMin = atof(strtok_s(NULL,"&",&next_token));
		model_info.zWidth = atoi(strtok_s(NULL,"&",&next_token));
		model_info.muid = atol(strtok_s(NULL,"&",&next_token));
		char temp[2];
		fileStream->read(temp, 1);
		initModelArray();
		fileStream->read(model_info.modelArr, arrLength);
		return SF_STS_FAIL;
	}

	const Model::Model_Info* Model::getModelInfo()
	{
		return &model_info;
	}

	const Model::Person_Info* Model::getPersonInfo()
	{
		return &person_info;
	}

	//Omits " " if name part is "".
	//Assumes the user always inputs last name
	SF_NAME Model::getConcatenatedName()
	{
		string name = "";
		
		if (this->person_info.salutation != "")
			name.append(this->person_info.salutation + " ");

		if (this->person_info.firstName != "")
			name.append(this->person_info.firstName + " ");

		if (this->person_info.middleName != "")
			name.append(this->person_info.middleName + " ");

		if (this->person_info.lastName != "")
			name.append(this->person_info.lastName);

		if (this->person_info.suffix != "")
			name.append(" " + this->person_info.suffix);

		return name;
	}

	//Omits "_" if name part is "". 
	//Assumes the user always inputs last name
	SF_NAME Model::getFileVersionName()
	{
		string name = "";
		
		if (this->person_info.salutation != "")
			name.append(this->person_info.salutation + "_");

		if (this->person_info.firstName != "")
			name.append(this->person_info.firstName + "_");

		if (this->person_info.middleName != "")
			name.append(this->person_info.middleName + "_");

		if (this->person_info.lastName != "")
			name.append(this->person_info.lastName);

		if (this->person_info.suffix != "")
			name.append("_" + this->person_info.suffix);

		return name;
	}

	const SF_NAME Model::getSalutation()
	{
		return this->person_info.salutation;
	}

	const SF_NAME Model::getFirstName()
	{
		return this->person_info.firstName;
	}

	const SF_NAME Model::getMiddleName()
	{
		return this->person_info.middleName;
	}

	const SF_NAME Model::getLastName()
	{
		return this->person_info.lastName;
	}

	const SF_NAME Model::getSuffix()
	{
		return this->person_info.suffix;
	}

	SF_STS Model::setGender(SF_GENDER gender)
	{
		person_info.gender = gender;
		int i = 0;
		while (person_info.gender[i]){
			person_info.gender[i] = tolower(person_info.gender[i]);	
			i++;
		}
		return SF_STS_OK;
	}

	
	Model::~Model(void)
	{
		if(this->model_info.modelArr)
			delete[] this->model_info.modelArr;
	}

	const SF_MODEL_ARR Model::getReadOnlyModelArr(){return model_info.modelArr;}
	SF_MODEL_ARR Model::getWritableModelArr(){return model_info.modelArr;}

	void Model::setPersonUID(const SF_PUID puid){person_info.puid = puid;}
	void Model::setModelUID(const SF_MUID muid){model_info.muid = muid;}
	const SF_PUID Model::getPersonUID(){return person_info.puid;}
	const SF_MUID Model::getModelUID(){return model_info.muid;}
	const SF_GENDER Model::getGender(){return person_info.gender;}
	const SF_EMAIL Model::getEmail(){return person_info.emailAddress;}

}