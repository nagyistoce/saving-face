#include "stdafx.h"
#include "CppUnitTest.h"
#include "sf_util.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SavingFaceTest
{
	TEST_CLASS(utilitiesTest)
	{
	public:
		
		TEST_METHOD(MakeDirectoryTest)
		{
			string path = "RandomDirectory";
			removeDirectory(path);
			//remove first in case test previously failed;
			Assert().IsFalse(doesDirectoryExist(getFullPath(path)),L"Directory Already Exists");
			Assert().IsTrue(makeDirectory(path) == SF_STS_OK,L"Failed to make directory");
			if(doesDirectoryExist(getFullPath(path))){
				string str = "Directory " + getFullPath(path) + " exists\n";
				Logger().WriteMessage(str.c_str());
			}else{
				string str = "Directory " + getFullPath(path) + " creation failed!\n";
				Logger().WriteMessage(str.c_str());
				Assert().Fail(L"Directory Creation Failed");
			}
			Assert().IsTrue(removeDirectory(path) == SF_STS_OK,L"Remove Directory Failed");
			Assert().IsFalse(doesDirectoryExist(getFullPath(path)),L"Remove Directory Failed");
		}

	};
}