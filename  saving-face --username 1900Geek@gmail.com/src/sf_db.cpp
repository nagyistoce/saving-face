#include "sf_db.h"


sf_db::sf_db(void)
{
	
}


sf_db::~sf_db(void)
{
	//TODO delete all remaining database entries.
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
	if ( db.find(muid) == db.end() ) {
		
		return NULL;
	} 

	else {
	return db[muid];
	}
	
	
}

//iterate over all models and save to persistant storage
SF_STS sf_db::saveDatabase(string path)
{
	ofstream *out = new ofstream(path);

	std::map<SF_MUID, Model*>::iterator iter;
    std::string* strToReturn = new std::string("");

     for (iter = db.begin(); iter != db.end(); iter++) {

		iter->second->streamToFile(out);
		out->write("|", 1);
        }

	 return SF_STS_FAIL;
}

	//load all models in the path with file extension .mdl
	SF_STS sf_db::loadDatabase(string path)
	{
		SF_STS sts = SF_STS_OK;

		ifstream *in = new ifstream(path);
		Model *model = new Model();
		char *next_token = NULL;
		
		while(!in->end)
		{
			model->loadFromFile(in);
			char temp[2];
			in->read(temp, 1);
			sts = addModelToDatabase(model);
		}

		in->close();
		return sts;
	}


