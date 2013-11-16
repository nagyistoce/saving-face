#pragma once
#include <vector>
#include "sf_model.h"

using namespace SF;
using namespace std;
class sf_db
{
public:
	sf_db(void);
	~sf_db(void);

	SF_STS saveDatabase();
	SF_STS loadDatabase(string path);
	SF_STS addModelToDatabase();
	SF_STS deleteModelFromDatabase();
	
	//return type yet unknown
	void compareToModels(/*a function pointer to a model comparison algorithm*/);

private:
	vector<Model> *db;
};

