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

	SF_STS Model::streamToFile(ofstream const *fileStream)
	{
		//TODO
		return SF_STS_FAIL;
	}

	SF_STS Model::loadFromFile(ifstream const *fileStream)
	{
		//TODO
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

	// TODO Omit "_" if name part is "".
	SF_NAME Model::getConcatenatedName()
	{
		string name = person_info.salutation + " " 
			+ person_info.firstName + " " 
			+ person_info.middleName + " " 
			+ person_info.lastName + " " 
			+ person_info.suffix;
		return name;
	}

	// TODO Omit "_" if name part is "". 
	SF_NAME Model::getFileVersionName()
	{
		string name = person_info.salutation + "_" 
			+ this->person_info.firstName + "_" 
			+ this->person_info.middleName + "_" 
			+ this->person_info.lastName + "_" 
			+ this->person_info.suffix;
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

	const SF_GENDER Model::getGender()
	{
		return this->person_info.gender;
	}

	const SF_EMAIL Model::getEmail()
	{
		return this->person_info.emailAddress;
	}

	Model::~Model(void)
	{
		if(this->model_info.modelArr)
			delete[] this->model_info.modelArr;
	}

	const SF_MODEL_ARR Model::getReadOnlyModelArr()
	{
		return model_info.modelArr;
	}

	SF_MODEL_ARR Model::getWritableModelArr()
	{
		return model_info.modelArr;
	}

}