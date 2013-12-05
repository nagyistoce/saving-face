#include "sf_model_builder.h"
#include <time.h>
#include <iostream>
#include <math.h>
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

	SF_MUID sf_model_builder::addNewModel(SF_NAME const salutation, SF_NAME const firstName, SF_NAME const middleName, SF_NAME const lastName, SF_NAME const suffix,SF_GENDER const gender,  SF_EMAIL const email)
	{
		Model *model = new Model(salutation, firstName, middleName,lastName, suffix, gender, email);
		SF_UID_TYPE uid = generateUID();
		model->setModelUID(uid);
		model->setPersonUID(uid);
		model->initModelArray();
		temp_db.addModelToDatabase(model);
		return uid;
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


	//This would have to be changed for multi-threading.
	//Would require a template class.
	namespace MB
	{
		//Here is a departure from OOP for the sake of speed.
		SF_TR_MATRIX *trMatrix;
		//Has all required info to build the model.
		SF::Model::Model_Info const *currentModelInfo = 0;
		SF::SF_MODEL_ARR arr = 0; 
		
		void getTr(SF_YPR* ypr, SF_R3_COORD* trCoord,void *thisClass)
		{
			//if(((sf_model_builder*)thisClass)->currentTr)
			//	delete ((sf_model_builder*)thisClass)->currentTr;
			//TODO this creates a memory leak.
			SF_YPR radYPR;
			radYPR.yaw = -(ypr->yaw * _SF_PI / 180.0f);
			radYPR.pitch = -(ypr->pitch * _SF_PI / 180.0f);
			radYPR.roll = -(ypr->roll * _SF_PI / 180.0f);
			((sf_model_builder*)thisClass)->currentTr = new SF_TR_MATRIX;
			calculateTRMatrix(*((sf_model_builder*)thisClass)->currentTr, *trCoord, radYPR);
			//Assigns to local/Global var. (Fast access for many thousands of calls)
			trMatrix = ((sf_model_builder*)thisClass)->currentTr;
		}

		void processVertex(SF_R3_COORD& coord,void *thisClass)
		{
			SF_MODEL_COORD3D modelCoord;
			SF_MODEL_COORD3D_INDEX index;
			transformCoord(modelCoord, coord, *trMatrix);
			coordInModelSpace(index, modelCoord, currentModelInfo);
			//Important check... Make sure is within model coords.
			//The best way to do this would be to gaurentee that any possible coord that makes it this
			//far is valid by limiting the search space
			//Otherwise the following check is necessary.
			if(index.x >= 0 &&index.x < currentModelInfo->xWidth 
				&& index.y >= 0 &&index.y < currentModelInfo->yWidth
				&& index.z >= 0 &&index.z < currentModelInfo->zWidth){

				int num = index.x * currentModelInfo->xOffset + index.y * currentModelInfo->yOffset + index.z;
				arr[num]++;
			}
		}

		void onNewFrame(int frameNumber)
		{

		}
}

	//called after calling addNewModel then pass in the muid
	SF_STS sf_model_builder::buildModel(SF_MUID muid,SF_Session *session,bool saveVideo)
	{
		currentModel = muid;
			
		string fileName = getModel(muid)->getFileVersionName();
		fileName += ".vdo";
		if(!saveVideo){
			if(session->captureStreams() < SF_STS_OK)
				return SF_STS_FAIL;
		}else
		{
			if(session->captureStreams(fileName,true) < SF_STS_OK)
				return SF_STS_FAIL;
		}
		session->createDepthRenderView();
		session->createColorRenderView();
		session->loadFaceModule();

		MB::currentModelInfo = getModel(muid)->getModelInfo();
		MB::arr = getModel(muid)->getWritableModelArr();
		session->camera_loop(&MB::getTr,&MB::processVertex,NULL,NULL,NULL,this,500);
		int len = getModel(muid)->getArrLength();
		session->releaseStreams();
		for(int i = 0; i < len; i++)
			if(MB::arr[i] < 0x0B)  MB::arr[i] = 0;
		MB::currentModelInfo = 0;
		MB::arr = 0;
		return SF_STS_OK;
	}

	SF_STS sf_model_builder::saveToDatabase(SF_MUID muid,sf_db *sfdb)
	{
		return sfdb->addModelToDatabase(getModel(muid));
	}

	Model *sf_model_builder::getModel(SF_MUID muid)
	{
		return temp_db.getModel(muid);
	}

	SF_STS sf_model_builder::deleteModel(SF_MUID muid)
	{
		return temp_db.deleteModelFromDatabase(muid);
	}
