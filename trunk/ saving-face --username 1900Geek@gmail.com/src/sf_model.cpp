#include "sf_model.h"

namespace SF
{
	Model::Model(void)
	{
		this->model_info.modelArr = 0;
		setDefaultParameters();
	}

	SF_STS Model::setName(SF_NAME salutation, SF_NAME firstName, SF_NAME middleName, SF_NAME lastName, SF_NAME suffix)
	{
		this->person_info.salutation = salutation;
		this->person_info.firstName = firstName;
		this->person_info.middleName = middleName;
		this->person_info.lastName = lastName;
		this->person_info.suffix = suffix;
		

		//TODO: error checking and return status
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

	SF_STS Model::initModelArray()
	{
		if(this->model_info.modelArr){
			delete[] this->model_info.modelArr;
			this->model_info.modelArr = 0;
		}
		this->model_info.modelArr = new SF_MODEL_UNIT[this->model_info.xWidth * this->model_info.yWidth * this->model_info.zWidth];
		//Set model array to zero
		memset(this->model_info.modelArr,0,this->model_info.xWidth * this->model_info.yWidth * this->model_info.zWidth);
		if(this->model_info.modelArr)
			return SF_STS_OK;
		//Insert Seperate Fail Condition For Debug and Release
		else
			return SF_STS_MEM_ALLOC_FAIL;
	}
	
	SF_STS Model::setEmail(SF_EMAIL emailAddress)
	{
		this->person_info.emailAddress = emailAddress;
		return SF_STS_OK;
	}

	SF_STS Model::streamToFile(ofstream const *fileStream)
	{
		//TODO
		return 0;
	}

	SF_STS Model::loadFromFile(ifstream const *fileStream)
	{
		//TODO
		return 0;
	}

	const Model::Model_Info Model::getModelInfo()
	{
		return model_info;
	}

	const Model::Person_Info Model::getPersonInfo()
	{
		return person_info;
	}

	const SF_NAME Model::getConcatenatedName()
	{
		return this->person_info.salutation + " " + this->person_info.firstName + " " + this->person_info.middleName + " " + this->person_info.lastName + " " + this->person_info.suffix;
	}

	const SF_NAME Model::getFileVersionName()
	{
		return this->person_info.salutation + "_" + this->person_info.firstName + "_" + this->person_info.middleName + "_" + this->person_info.lastName + "_" + this->person_info.suffix;
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
		this->person_info.gender = gender;
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
}