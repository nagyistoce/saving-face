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

	//called after calling addNewModel then pass in the muid
	/*Model buildModel(SF_MUID muid)
	{
		SF::SF_Session *session = new SF::SF_Session();
		session->camera_loop(&getTr,&processVertex,NULL,NULL,NULL,100);
		return NULL;
	}*/

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
		SF_TR_MATRIX* getTr(SF_YPR* ypr, SF_R3_COORD* trCoord)
		{
			SF_TR_MATRIX *tr;
			//added
			tr = new SF_TR_MATRIX();
			calculateTRMatrix(*tr, *trCoord, *ypr);
			return tr;

			//here it seems it would be best to store the tr in a private variable for future use
			//Can't define this is sf_model_buidler.h and use as a callback function.
		}

		void processVertex(SF_R3_COORD& coord)
		{
			//pseudo
			SF_MODEL_COORD3D modelCoord;
			SF_MODEL_COORD3D_INDEX index;

			//this is where we would want to use the private variable tr and the model(or muid)

			//transformCoord(modelCoord, coord, tr);
			//coordInModelSpace(index, modelCoord, model->modelInfo());
			//model->getWritableModelArr()[index] = modelCoord;
		}

		void onNewFrame(int frameNumber)
		{

		}
}
	Model *sf_model_builder::getModel(SF_MUID muid)
	{
		return temp_db.getModel(muid);
	}

	SF_STS sf_model_builder::deleteModel(SF_MUID muid)
	{
		return temp_db.deleteModelFromDatabase(muid);
	}
