#include "sf_db.h"


sf_db::sf_db(void)
{
	db = new vector<Model>();
}


sf_db::~sf_db(void)
{
	delete db;
}
