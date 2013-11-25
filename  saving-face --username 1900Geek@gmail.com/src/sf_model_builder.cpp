#include "sf_model_builder.h"
#include <time.h>
#include <iostream>
#include "sf_tr_func.h"



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

	namespace MB
	{
		SF_TR_MATRIX *tr_current;
		void getTr(SF_YPR* ypr, SF_R3_COORD* trCoord)
		{
			//calculateTRMatrix(&tr_current, *trCoord, *ypr);

		}

		void processVertex(SF_R3_COORD& coord)
		{
			//pseudo
			//SF_MODEL_COORD3D modelCoord;
			//SF_MODEL_COORD3D_INDEX index;

			//this is where we would want to use the private variable tr and the model(or muid)

			//transformCoord(modelCoord, coord, tr);
			//coordInModelSpace(index, modelCoord, model->modelInfo());
			//model->getWritableModelArr()[index] = modelCoord;
		}

		void onNewFrame(int frameNumber)
		{

		}
}

	//called after calling addNewModel then pass in the muid
	void sf_model_builder::buildModel(SF_MUID muid)
	{
		currentModel = muid;
		SF::SF_Session *session = new SF::SF_Session();
		session->camera_loop(&MB::getTr,&MB::processVertex,NULL,NULL,NULL,100);
	}
	Model *sf_model_builder::getModel(SF_MUID muid)
	{
		return temp_db.getModel(muid);
	}

	SF_STS sf_model_builder::deleteModel(SF_MUID muid)
	{
		return temp_db.deleteModelFromDatabase(muid);
	}
