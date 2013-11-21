#pragma once
#include "sf_db.h"

using namespace SF;
using namespace std;
class sf_util
{
public:
	string getFullPath();

	void makeDirectory();

private:
	string path;
};