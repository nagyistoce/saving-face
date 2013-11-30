#include "sf_controller.h"


sf_controller::sf_controller(void)
{
}


sf_controller::~sf_controller(void)
{
}


SF_MUID sf_controller::createModel(SF_NAME const salutation, SF_NAME const firstName, SF_NAME const middleName, SF_NAME const lastName, SF_NAME const suffix,SF_GENDER const gender,  SF_EMAIL const email)
{
	//TODO check required parameters.
	//if(...)
	//	return -1;
	return mBuilder->addNewModel(salutation, firstName, middleName, lastName, suffix, gender, email);
}
	
namespace SF_CNT_PHOTO
{
	bool finished = false;
	bool takePhoto = false;

	bool shutterPressed()
	{
		if(takePhoto){
			takePhoto = false;
			return true;
		}
		return false;
	}

	bool areFinished()
	{
		if(finished)
		{
			finished = false;
			return true;
		}
		return false;
	}
}

SF_STS sf_controller::takeSnapshot(SF_MUID modelId)
{
	return session->snapshotLoop(mBuilder->getModel(modelId),&SF_CNT_PHOTO::shutterPressed,&SF_CNT_PHOTO::areFinished);
}

//Take the photo and return the filePath
void sf_controller::pressShutter()
{
	SF_CNT_PHOTO::takePhoto = true;
	
}
	
//Close the Snapshot video feed
void sf_controller::snapshotFinished()
{
	SF_CNT_PHOTO::finished = true;
}

string sf_controller::getSnapshotPath(SF_MUID modelID)
{
	return "";
}

SF_STS sf_controller::buildModel(SF_MUID modelID)
{
	//Check for valid photo.
		//return -1;
	return mBuilder->buildModel(modelID);
}
	
	
SF_STS sf_controller::command(string textCommand)
{
	return SF_STS_FAIL;
}

SF_STS sf_controller::init(string mode)
{
	//Check for alternative modes and implement logic as needed.
	db = new sf_db();
	db->loadDatabase(_DEFAULT_DB_DIR);
	mBuilder = new sf_model_builder();
	session = new SF_Session();
	if(!(session->createSession()))
		return SF_STS_FAIL;		
	if(!(session->setOptions(NULL, NULL)))
		return SF_STS_FAIL;
	return SF_STS_OK;
}