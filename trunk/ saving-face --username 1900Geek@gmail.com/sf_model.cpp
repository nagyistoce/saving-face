#include "sf_model.h"

namespace SF
{
	Model::Model(void)
	{
		modelArr = 0;
		//Temp Code For Testing
		setName("Mr","Bob","Elizabeth","Barker","III");
		
		setDefaultParameters();
		
		//Temp for testing.
		//Would not want to do this if loading from a file
		initModelArray();

	}

	SF_STS Model::setName(SF_NAME salutation, SF_NAME firstName, SF_NAME middleName, SF_NAME lastName, SF_NAME suffix)
	{
		this->salutation = salutation;
		this->firstName = firstName;
		this->middleName = middleName;
		this->lastName = lastName;
		this->suffix = suffix;

		//TODO: error checking and return status
		return SF_STS_OK;
	}

	SF_STS Model::setDefaultParameters()
	{
		xMin = SF_DEFAULT_XMIN;
		yMin = SF_DEFAULT_YMIN;
		zMin = SF_DEFAULT_ZMIN;
		xMax = SF_DEFAULT_XMAX;
		yMax = SF_DEFAULT_YMAX;
		zMax = SF_DEFAULT_ZMAX;
		deltaX = SF_DEFAULT_DELTAX;
		deltaY = SF_DEFAULT_DELTAY;
		deltaZ = SF_DEFAULT_DELTAZ;
		xWidth = (SF_ARR_WIDTH)((xMax - xMin) / deltaX);//Potential bug if value is not a perfect integer
		//for now assume it is. But Will fail on Apply coord in integration testing if not.
		yWidth = (SF_ARR_WIDTH)((yMax - yMin) / deltaY);
		zWidth = (SF_ARR_WIDTH)((zMax - zMin) / deltaZ);
		xOffset =(yWidth * zWidth);
		yOffset = zWidth;
		return SF_STS_OK;
	}

	SF_STS Model::initModelArray()
	{
		if(modelArr){
			delete modelArr;
			modelArr = 0;
		}
		modelArr = new SF_MODEL_UNIT[xWidth * yWidth * zWidth];
		if(modelArr)
			return SF_STS_OK;
		//Insert Seperate Fail Condition For Debug and Release
		else
			return SF_STS_MEM_ALLOC_FAIL;
	}
		

	Model::~Model(void)
	{
	}
}