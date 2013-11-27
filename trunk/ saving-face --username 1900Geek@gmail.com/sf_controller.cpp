#include "sf_controller.h"


sf_controller::sf_controller(void)
{
}


sf_controller::~sf_controller(void)
{
}


SF_MUID sf_controller::createModelModel(SF_NAME const salutation, SF_NAME const firstName, SF_NAME const middleName, SF_NAME const lastName, SF_NAME const suffix,SF_GENDER const gender,  SF_EMAIL const email)
{
	//TODO check required parameters.
	//if(...)
	//	return -1;
	return mBuilder->addNewModel(salutation, firstName, middleName, lastName, suffix, gender, email);
}
	
SF_STS sf_controller::takeSnapshot(SF_MUID modelID)
{
	return SF_STS_FAIL;
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