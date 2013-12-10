#include "sf_model_cmp.h"


using namespace SF;
namespace SF
{
		sf_model_cmp::sf_model_cmp(sf_db *db, SF_Session *session)
		{
			this->db = db;
			this->session = session;
			this->builder = new sf_model_builder();
			models = 0;
		}
		sf_model_cmp::~sf_model_cmp()
		{
			delete builder;
		}

		//A First Crude Implementation
		//Uses a fully constructed model
		//To later be replaced by multiple
		//implementations that call an observer
		sf_model_cmp::cmp_results *sf_model_cmp::compare()
		{	
			SF_MUID muid = builder->addNewModel();
			SF_STS sts = builder->buildModel(muid,session,false);
			model = builder->getModel(muid);
			SF_MODEL_ARR arr = model->getReadOnlyModelArr();
			int length = model->getArrLength();
			getModelReferences();
			int score[50]= {0};
			for(int i = 0; i < length; i++)
			{
				if(arr[i] == 0) continue;
				for(int m = 0; m < numModels; m++)
				{
					score[m] += models[m]->getReadOnlyModelArr()[i];
				}
			}
			cmp_results *res = new cmp_results();
			for(int m = 0; m < numModels; m++)
			{
				res->names.push_back(models[m]->getConcatenatedName());
				res->scores.push_back(score[m]);
				res->imagePaths.push_back(getFullPath(_DEFAULT_IMAGE_DIR) + models[m]->getFileVersionName() + ".BMP");
			}
			return res;
		}

		SF_STS sf_model_cmp::getModelReferences()
		{
			if(models)
				delete[] models;
			models = new Model*[50];
			db->getModelList(models,numModels);
			return SF_STS_FAIL;
		}
}