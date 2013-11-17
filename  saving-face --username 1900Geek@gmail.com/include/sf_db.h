#pragma once
#include <map>
#include "sf_model.h"

using namespace SF;
using namespace std;
class sf_db
{
public:
	sf_db(void);
	~sf_db(void);

	//iterate over all models and save to persistant storage
	SF_STS saveDatabase(string path);

	//load all models in the path with file extension .mdl
	SF_STS loadDatabase(string path);

	//push a model onto the database
	SF_STS addModelToDatabase(Model *model);

	//remove a model from the database
	SF_STS deleteModelFromDatabase(SF_MUID *modelID);
	
	//Can be simple... Single comparison algorithm... (Recomended)
	//Simple/Fast case is that all models have identical model_info structs.
	//More complex is to allow for differnt model resolutions... (Later)
	//return type yet unknown
	void compareToModels(/*a function pointer to a model comparison algorithm*/);

	//Returns a reference to the model class.
	//Eleminates the need for wrapper functions
	Model *getModel(SF_MUID muid);

private:
	//Store all models/
	map<SF_MUID, Model*> db;
};

