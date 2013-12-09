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

		//temp until call back is added
		sf_model_cmp::cmp_results *sf_model_cmp::compare()
		{
			//A First Crude Implementation
			SF_MUID muid = builder->addNewModel();
			SF_STS sts = builder->buildModel(muid,session,false);
			model = builder->getModel(muid);
			SF_MODEL_ARR arr = model->getReadOnlyModelArr();
			return 0;
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