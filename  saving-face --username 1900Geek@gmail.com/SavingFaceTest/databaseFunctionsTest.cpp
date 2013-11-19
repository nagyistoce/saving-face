#include "stdafx.h"
#include "CppUnitTest.h"
#include "sf_db.h"
#include "sf_model.h"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SF;
namespace SavingFaceTest
{
	TEST_CLASS(databaseFunctionsTest)
	{
	public:

		TEST_METHOD(testDatabaseAddGetModel)
		{
			sf_db *db = new sf_db;
			Model *modelOne, *modelTwo, *modelThree;
			modelOne = new Model("MD.","Punish","Me", "Please", "Sr", "Male","Owww@drPain.com");
			modelTwo = new Model("Mr.","Joe","F", "Dirt", "Jr", "Male","DirtJoe@email.com");
			modelThree = new Model("Dr.","Gordon","P", "Freeman", "I", "Male","gordon@valve.com");

			modelOne->setPersonUID(111111L);
			modelOne->setModelUID(222222L); 
			SF_MUID expMUIDOne = modelOne->getModelUID();

			modelTwo->setPersonUID(333333L);
			modelTwo->setModelUID(444444L); 
			SF_MUID expMUIDTwo = modelOne->getModelUID();

			modelThree->setPersonUID(555555L);
			modelThree->setModelUID(666666L); 
			SF_MUID expMUIDThree = modelOne->getModelUID();

			string expConcatNameOne = modelOne->getConcatenatedName();
			string expConcatNameTwo = modelTwo->getConcatenatedName();
			string expConcatNameThree = modelThree->getConcatenatedName();

			if (db->addModelToDatabase(modelOne))
				Logger().WriteMessage(L"Model one added to database.");
			else
				Logger().WriteMessage(L"Model one failed adding to database.");
			
			db->addModelToDatabase(modelTwo);
			db->addModelToDatabase(modelThree);

			delete modelOne;
			delete modelTwo;
			delete modelThree;

			modelOne = 0;
			modelTwo = 0;
			modelThree = 0;

			modelOne = new Model();
			modelTwo = new Model();
			modelThree = new Model();

			modelOne = db->getModel(expMUIDOne);

			if (modelOne == nullptr)
				Logger().WriteMessage(L"\nModel one failed to get from database.");
			else
			{
				Logger().WriteMessage(L"\nModel one retrieved from database.");
				Logger().WriteMessage(modelOne->getFirstName().c_str());
			}

			

			modelTwo = db->getModel(expMUIDTwo);
			modelThree = db->getModel(expMUIDThree);

			Assert().IsTrue(expMUIDOne == modelOne->getModelUID(),L"MUID is not equal");
			Assert().AreEqual(expConcatNameOne, modelOne->getConcatenatedName(),L"Names are not equal");
			Assert().AreEqual(expConcatNameTwo, modelTwo->getConcatenatedName(),L"Names are not equal");
			Assert().AreEqual(expConcatNameThree, modelThree->getConcatenatedName(),L"Names are not equal");

			delete modelOne;
			delete modelTwo;
			delete modelThree;

			delete db;

			Assert().Fail(L"Unfinished");
		}

		TEST_METHOD(testDatabaseFileIOStreams)
		{
			Assert().Fail(L"Unfinished");
		}


	};
}