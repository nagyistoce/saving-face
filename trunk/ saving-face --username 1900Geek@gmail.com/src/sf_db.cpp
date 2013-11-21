#include "sf_db.h"
#include <windows.h>

sf_db::sf_db(void)
{

}


sf_db::~sf_db(void)
{
	db.clear();
}

SF_STS sf_db::addModelToDatabase(Model  *model)
{
	//second condition is to make sure it's not in the database already
	if(model && db.find(model->getModelUID()) == db.end()) 
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
//TODO:  delete file if database fails to save
SF_STS sf_db::saveDatabase(string path)
{
	std::map<SF_MUID, Model*>::iterator iter;

	SF_STS status = SF_STS_OK;
     for (iter = db.begin(); iter != db.end(); iter++) 
	 {
		//saving file as (file version name).mdl
		 ofstream *out = new ofstream(path + db[iter->first]->getFileVersionName() + ".mdl");
			status = (!status) ? SF_STS_FAIL : iter->second->streamToFile(out);
			delete out;
	 }

	 return status;
}

SF_STS sf_db::deleteModelFromDatabase(SF_MUID modelID)
{
	if (db.find(modelID) != db.end())
		db.erase(modelID);

	if (db.find(modelID) == db.end())
	{
		return SF_STS_OK; //no longer in database
	}

	return SF_STS_FAIL;
}

	//load all models in the path with file extension .mdl
	SF_STS sf_db::loadDatabase(string path)
	{
		SF_STS status = SF_STS_OK;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		WIN32_FIND_DATA ffd;
		string wwcStr = path + "*.mdl";
		hFind = FindFirstFile(wwcStr.c_str(), &ffd);

		if (hFind == INVALID_HANDLE_VALUE) 
		{
			status = SF_STS_FAIL; //error searching directory
		}else
		do {
			string filePath = path + ffd.cFileName;
			ifstream *in = new ifstream(filePath);
			Model *model = new Model();
			model->loadFromFile(in);
			in->close();
			delete in;
			addModelToDatabase(model);
	  } while (FindNextFile(hFind, &ffd) != 0);

	  if (GetLastError() != ERROR_NO_MORE_FILES) {
		status = SF_STS_FAIL;
	  }
		
		return status;
	}


