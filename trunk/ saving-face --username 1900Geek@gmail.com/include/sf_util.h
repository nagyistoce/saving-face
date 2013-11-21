#pragma once
#include "sf_db.h"

using namespace SF;
using namespace std;
//Shouldn't be a class.
//These are utility functions
//No need to store the path.
class sf_util
{
public:
	string getFullPath(string partialPath);

	void makeDirectory(string partialPath);

};