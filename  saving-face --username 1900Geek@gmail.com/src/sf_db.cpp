#include "sf_db.h"


sf_db::sf_db(void)
{
	
}


sf_db::~sf_db(void)
{
}

SF_STS sf_db::addModelToDatabase(Model  *model)
{
	if(model)
	{
		db[model->getModelUID()] = model;
		return SF_STS_OK;
	}else
		return SF_STS_FAIL;
}

Model *sf_db::getModel(SF_MUID muid)
{
	return db[muid];
}

