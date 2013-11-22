#pragma once
#include "sf_db.h"

using namespace SF;
using namespace std;

namespace SF
{
	const string getFullPath(string const partialPath);
	bool doesDirectoryExist(string const fullPath);
	SF_STS removeDirectory(string const partialPath);
	SF_STS makeDirectory(string const partialPath);
}
