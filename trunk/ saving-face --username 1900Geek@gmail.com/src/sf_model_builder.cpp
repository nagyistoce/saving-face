#include "sf_model_builder.h"
#include <time.h>
namespace SF
{
	sf_model_builder::sf_model_builder(void)
	{
	}


	sf_model_builder::~sf_model_builder(void)
	{
	}

	SF_UID_TYPE sf_model_builder::generateUID()
	{
		time_t t;
		time(&t);
		return (long)t;
	}

	SF_MUID sf_model_builder::addNewModel()
	{
		Model *model = new Model();
		SF_UID_TYPE uid = generateUID();
		model->setModelUID(uid);
		model->setPersonUID(uid);
		model->initModelArray();
		temp_db.addModelToDatabase(model);
		return uid;
	}

	//Temp Implementation For Testing.
	Model *sf_model_builder::buildModel(SF_Session *session, SF_MUID muid)
	{
		Model *mdl = temp_db.getModel(muid);
		if(mdl == nullptr) 
			return nullptr;
		session->camera_loop((&getTr),&processVertex,NULL,&onNewFrame,NULL,128);
	}

	void getTr(SF_YPR* ypr, SF_R3_COORD* trCoord)
	{

	}

	void processVertex(SF_R3_COORD& coord)
	{

	}

	void onNewFrame(int frameNumber)
	{

	}

	Model *sf_model_builder::getModel(SF_MUID muid)
	{
		return temp_db.getModel(muid);
	}

	SF_STS sf_model_builder::deleteModel(SF_MUID muid)
	{
		return temp_db.deleteModelFromDatabase(muid);
	}

}