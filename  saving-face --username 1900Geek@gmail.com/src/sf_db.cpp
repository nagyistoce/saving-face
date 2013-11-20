#include "sf_db.h"


sf_db::sf_db(void)
{

}


sf_db::~sf_db(void)
{
	db.clear();
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
	if ( db.find(muid) == db.end() )
	{
		//probably should throw an exception
		return nullptr;
	} 

	else {
		return db.find(muid)->second;
	}
	
	
}

//iterate over all models and save to persistant storage
SF_STS sf_db::saveDatabase(string path)
{
	std::map<SF_MUID, Model*>::iterator iter;
    //std::string* strToReturn = new std::string("");

     for (iter = db.begin(); iter != db.end(); iter++) 
	 {
		//saving file as (muid).mdf
			ofstream *out = new ofstream(path + to_string(iter->first) + ".mdf");
			iter->second->streamToFile(out);
			delete out;
	 }

	 return SF_STS_FAIL;
}

	//load all models in the path with file extension .mdl
	SF_STS sf_db::loadDatabase(string path)
	{
		SF_STS sts = SF_STS_OK;

		//TODO find every .mdf in the path
		//load the model and check to see if the muid is already in the map
		//if not store the loaded model in the map. -Andy

		//Need to examine path to find All .mdl files.
		ifstream *in = new ifstream(path);
		
	}


