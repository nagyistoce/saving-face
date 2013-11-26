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
		//Here is a departure from OOP for the sake of speed.
		SF_TR_MATRIX *trMatrix;
		//Has all required info to build the model.
		SF::Model::Model_Info const *currentModelInfo = 0;
		SF::SF_MODEL_ARR arr = 0; 
		void getTr(SF_YPR* ypr, SF_R3_COORD* trCoord,void *thisClass)
		{
			//How to call
			calculateTRMatrix(*((sf_model_builder*)thisClass)->currentTr, *trCoord, *ypr);
			//Assigns to local/Global var. (Fast access for many thousands of calls)
			trMatrix = ((sf_model_builder*)thisClass)->currentTr;
		}

		void processVertex(SF_R3_COORD& coord,void *thisClass)
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
		//TODO check to see that modelArr is initialized.
		SF::SF_Session *session = new SF::SF_Session();
		MB::currentModelInfo = getModel(muid)->getModelInfo();
		MB::arr = getModel(muid)->getWritableModelArr();
		session->camera_loop(&MB::getTr,&MB::processVertex,NULL,NULL,NULL,this,100);
		MB::currentModelInfo = 0;
		MB::arr = 0;
	}
	Model *sf_model_builder::getModel(SF_MUID muid)
	{
		return temp_db.getModel(muid);
	}

	SF_STS sf_model_builder::deleteModel(SF_MUID muid)
	{
		return temp_db.deleteModelFromDatabase(muid);
	}
