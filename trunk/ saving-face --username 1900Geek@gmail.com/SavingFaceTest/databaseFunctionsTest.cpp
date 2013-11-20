#include "stdafx.h"
#include "CppUnitTest.h"
#include "sf_db.h"
#include "sf_model.h"
#include <fstream>
#include <windows.h>
#include <direct.h>
#include <string>
#include <wchar.h>

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
			SF_MUID expMUIDTwo = modelTwo->getModelUID();

			modelThree->setPersonUID(555555L);
			modelThree->setModelUID(666666L); 
			SF_MUID expMUIDThree = modelThree->getModelUID();
			
			string expConcatNameOne = modelOne->getConcatenatedName();
			string expConcatNameTwo = modelTwo->getConcatenatedName();
			string expConcatNameThree = modelThree->getConcatenatedName();

			modelOne->initModelArray();
			modelTwo->initModelArray();
			modelThree->initModelArray();
			
			modelOne->getModelInfo()->modelArr[0] = 'A';
			modelOne->getModelInfo()->modelArr[1] = 'B';
			modelOne->getModelInfo()->modelArr[2] = 'C';

			modelTwo->getModelInfo()->modelArr[0] = 'P';
			modelTwo->getModelInfo()->modelArr[1] = 'Q';
			modelTwo->getModelInfo()->modelArr[2] = 'R';

			modelThree->getModelInfo()->modelArr[0] = 'X';
			modelThree->getModelInfo()->modelArr[1] = 'Y';
			modelThree->getModelInfo()->modelArr[2] = 'Z';

			SF_DELTA expDeltaX = modelOne->getModelInfo()->deltaX;
			SF_BOUND expXMax = modelOne->getModelInfo()->xMax;
			SF_BOUND expXMin = modelOne->getModelInfo()->xMin;
			SF_ARR_OFFSET expXOffset = modelOne->getModelInfo()->xOffset;
			SF_ARR_WIDTH expXWidth = modelOne->getModelInfo()->xWidth;

			SF_DELTA expDeltaY = modelOne->getModelInfo()->deltaY;
			SF_BOUND expYMax = modelOne->getModelInfo()->yMax;
			SF_BOUND expYMin = modelOne->getModelInfo()->yMin;
			SF_ARR_OFFSET expYOffset = modelOne->getModelInfo()->yOffset;
			SF_ARR_WIDTH expYWidth = modelOne->getModelInfo()->yWidth;

			SF_DELTA expDeltaZ = modelOne->getModelInfo()->deltaZ;
			SF_BOUND expZMax = modelOne->getModelInfo()->zMax;
			SF_BOUND expZMin = modelOne->getModelInfo()->zMin;
			SF_ARR_WIDTH expZWidth = modelOne->getModelInfo()->zWidth;


			Assert().IsTrue(db->addModelToDatabase(modelOne) == SF_STS_OK, L"Failed to add model to database.");
			Assert().IsTrue(db->addModelToDatabase(modelTwo) == SF_STS_OK, L"Failed to add model to database.");
			Assert().IsTrue(db->addModelToDatabase(modelThree) == SF_STS_OK, L"Failed to add model to database.");

			modelOne = 0;
			modelTwo = 0;
			modelThree = 0;

			modelOne = new Model();
			modelTwo = new Model();
			modelThree = new Model();

			//verify that the model has been reinitialized to default
			Assert().IsFalse(modelOne->getConcatenatedName().c_str() == expConcatNameOne.c_str(), L"Name should not match the expected name, yet.");
			Assert().IsFalse(modelTwo->getConcatenatedName().c_str() == expConcatNameTwo.c_str(), L"Name should not match the expected name, yet.");
			Assert().IsFalse(modelThree->getConcatenatedName().c_str() == expConcatNameThree.c_str(), L"Name should not match the expected name, yet.");

			modelOne = db->getModel(expMUIDOne);
			modelTwo = db->getModel(expMUIDTwo);
			modelThree = db->getModel(expMUIDThree);

			Assert().IsFalse(modelOne == nullptr, L"Failed to retrieve model from database.");
			Assert().IsFalse(modelTwo == nullptr, L"Failed to retrieve model from database.");
			Assert().IsFalse(modelThree == nullptr, L"Failed to retrieve model from database.");

			Assert().AreEqual(expMUIDOne, modelOne->getModelUID(),L"MUID is not equal");
			Assert().AreEqual(expConcatNameOne, modelOne->getConcatenatedName(),L"Names are not equal");
			Assert().IsTrue(modelOne->getPersonUID() == 111111L,L"PUID is not equal");
			Assert().IsTrue(modelOne->getSalutation() == "MD.", L"Salutation is not equal");
			Assert().IsFalse(modelOne->getSalutation() == "MD");
			Assert().IsTrue(modelOne->getFirstName() == "Punish", L"First name is not equal");
			Assert().IsFalse(modelOne->getFirstName() == "punish");
			Assert().IsTrue(modelOne->getMiddleName() == "Me", L"Middle name is not equal");
			Assert().IsFalse(modelOne->getMiddleName() == "me");
			Assert().IsTrue(modelOne->getLastName() == "Please", L"Last name is not equal");
			Assert().IsFalse(modelOne->getLastName() == "please");
			Assert().IsTrue(modelOne->getSuffix() == "Sr", L"Suffix is not equal");
			Assert().IsFalse(modelOne->getSuffix() == "Sr.");
			Assert().IsTrue(modelOne->getGender() == "male", L"Gender is not equal");
			Assert().IsFalse(modelOne->getGender() == "Male");
			Assert().IsTrue(modelOne->getEmail() == "Owww@drPain.com", L"Email is not equal");

			Assert().IsTrue(modelOne->getModelInfo()->deltaX == expDeltaX, L"deltaX is not equal");
			Assert().IsTrue(modelOne->getModelInfo()->xMax == expXMax, L"xMin is not equal");
			Assert().IsTrue(modelOne->getModelInfo()->xMin == expXMin, L"xMax is not equal");
			Assert().IsTrue(modelOne->getModelInfo()->xOffset == expXOffset, L"xOffset is not equal");
			Assert().IsTrue(modelOne->getModelInfo()->xWidth == expXWidth, L"xWidth is not equal");

			Assert().IsTrue(modelOne->getModelInfo()->deltaY == expDeltaY, L"deltaY is not equal");
			Assert().IsTrue(modelOne->getModelInfo()->yMax == expYMax, L"yMin is not equal");
			Assert().IsTrue(modelOne->getModelInfo()->yMin == expYMin, L"yMax is not equal");
			Assert().IsTrue(modelOne->getModelInfo()->yOffset == expYOffset, L"yOffset is not equal");
			Assert().IsTrue(modelOne->getModelInfo()->yWidth == expYWidth, L"yWidth is not equal");

			Assert().IsTrue(modelOne->getModelInfo()->deltaZ == expDeltaZ, L"deltaZ is not equal");
			Assert().IsTrue(modelOne->getModelInfo()->zMax == expZMax, L"zMin is not equal");
			Assert().IsTrue(modelOne->getModelInfo()->zMin == expZMin, L"zMax is not equal");
			Assert().IsTrue(modelOne->getModelInfo()->zWidth == expZWidth, L"zWidth is not equal");

			Assert().IsTrue(modelOne->getModelInfo()->modelArr[0] == 'A',L"Address 0 not equal");
			Assert().IsTrue(modelOne->getModelInfo()->modelArr[1] == 'B',L"Address 1 not equal");
			Assert().IsTrue(modelOne->getModelInfo()->modelArr[2] == 'C',L"Address 2 not equal");

			//Tests for model 2
			Assert().AreEqual(expMUIDTwo, modelTwo->getModelUID(),L"MUID is not equal");
			Assert().AreEqual(expConcatNameTwo, modelTwo->getConcatenatedName(),L"Names are not equal");
			Assert().IsTrue(modelTwo->getPersonUID() == 333333L,L"PUID is not equal");
			Assert().IsTrue(modelTwo->getSalutation() == "Mr.", L"Salutation is not equal");
			Assert().IsFalse(modelTwo->getSalutation() == "Mr");
			Assert().IsTrue(modelTwo->getFirstName() == "Joe", L"First name is not equal");
			Assert().IsFalse(modelTwo->getFirstName() == "joe");
			Assert().IsTrue(modelTwo->getMiddleName() == "F", L"Middle name is not equal");
			Assert().IsFalse(modelTwo->getMiddleName() == "f");
			Assert().IsTrue(modelTwo->getLastName() == "Dirt", L"Last name is not equal");
			Assert().IsFalse(modelTwo->getLastName() == "dirt");
			Assert().IsTrue(modelTwo->getSuffix() == "Jr", L"Suffix is not equal");
			Assert().IsFalse(modelTwo->getSuffix() == "jr");
			Assert().IsTrue(modelTwo->getGender() == "male", L"Gender is not equal");
			Assert().IsFalse(modelTwo->getGender() == "Male");
			Assert().IsTrue(modelTwo->getEmail() == "DirtJoe@email.com", L"Email is not equal");

			Assert().IsTrue(modelTwo->getModelInfo()->deltaX == expDeltaX, L"deltaX is not equal");
			Assert().IsTrue(modelTwo->getModelInfo()->xMax == expXMax, L"xMin is not equal");
			Assert().IsTrue(modelTwo->getModelInfo()->xMin == expXMin, L"xMax is not equal");
			Assert().IsTrue(modelTwo->getModelInfo()->xOffset == expXOffset, L"xOffset is not equal");
			Assert().IsTrue(modelTwo->getModelInfo()->xWidth == expXWidth, L"xWidth is not equal");

			Assert().IsTrue(modelTwo->getModelInfo()->deltaY == expDeltaY, L"deltaY is not equal");
			Assert().IsTrue(modelTwo->getModelInfo()->yMax == expYMax, L"yMin is not equal");
			Assert().IsTrue(modelTwo->getModelInfo()->yMin == expYMin, L"yMax is not equal");
			Assert().IsTrue(modelTwo->getModelInfo()->yOffset == expYOffset, L"yOffset is not equal");
			Assert().IsTrue(modelTwo->getModelInfo()->yWidth == expYWidth, L"yWidth is not equal");

			Assert().IsTrue(modelTwo->getModelInfo()->deltaZ == expDeltaZ, L"deltaZ is not equal");
			Assert().IsTrue(modelTwo->getModelInfo()->zMax == expZMax, L"zMin is not equal");
			Assert().IsTrue(modelTwo->getModelInfo()->zMin == expZMin, L"zMax is not equal");
			Assert().IsTrue(modelTwo->getModelInfo()->zWidth == expZWidth, L"zWidth is not equal");

			Assert().IsTrue(modelTwo->getModelInfo()->modelArr[0] == 'P',L"Address 0 not equal");
			Assert().IsTrue(modelTwo->getModelInfo()->modelArr[1] == 'Q',L"Address 1 not equal");
			Assert().IsTrue(modelTwo->getModelInfo()->modelArr[2] == 'R',L"Address 2 not equal");

			//Tests for model 3
			Assert().AreEqual(expMUIDThree, modelThree->getModelUID(),L"MUID is not equal");
			Assert().AreEqual(expConcatNameThree, modelThree->getConcatenatedName(),L"Names are not equal");
			Assert().IsTrue(modelThree->getPersonUID() == 555555L,L"PUID is not equal");
			Assert().IsTrue(modelThree->getSalutation() == "Dr.", L"Salutation is not equal");
			Assert().IsFalse(modelThree->getSalutation() == "dr.");
			Assert().IsTrue(modelThree->getFirstName() == "Gordon", L"First name is not equal");
			Assert().IsFalse(modelThree->getFirstName() == "gordon");
			Assert().IsTrue(modelThree->getMiddleName() == "P", L"Middle name is not equal");
			Assert().IsFalse(modelThree->getMiddleName() == "p");
			Assert().IsTrue(modelThree->getLastName() == "Freeman", L"Last name is not equal");
			Assert().IsFalse(modelThree->getLastName() == "freeman");
			Assert().IsTrue(modelThree->getSuffix() == "I", L"Suffix is not equal");
			Assert().IsFalse(modelThree->getSuffix() == "i");
			Assert().IsTrue(modelThree->getGender() == "male", L"Gender is not equal");
			Assert().IsFalse(modelThree->getGender() == "Male");
			Assert().IsTrue(modelThree->getEmail() == "gordon@valve.com", L"Email is not equal");

			Assert().IsTrue(modelThree->getModelInfo()->deltaX == expDeltaX, L"deltaX is not equal");
			Assert().IsTrue(modelThree->getModelInfo()->xMax == expXMax, L"xMin is not equal");
			Assert().IsTrue(modelThree->getModelInfo()->xMin == expXMin, L"xMax is not equal");
			Assert().IsTrue(modelThree->getModelInfo()->xOffset == expXOffset, L"xOffset is not equal");
			Assert().IsTrue(modelThree->getModelInfo()->xWidth == expXWidth, L"xWidth is not equal");

			Assert().IsTrue(modelThree->getModelInfo()->deltaY == expDeltaY, L"deltaY is not equal");
			Assert().IsTrue(modelThree->getModelInfo()->yMax == expYMax, L"yMin is not equal");
			Assert().IsTrue(modelThree->getModelInfo()->yMin == expYMin, L"yMax is not equal");
			Assert().IsTrue(modelThree->getModelInfo()->yOffset == expYOffset, L"yOffset is not equal");
			Assert().IsTrue(modelThree->getModelInfo()->yWidth == expYWidth, L"yWidth is not equal");

			Assert().IsTrue(modelThree->getModelInfo()->deltaZ == expDeltaZ, L"deltaZ is not equal");
			Assert().IsTrue(modelThree->getModelInfo()->zMax == expZMax, L"zMin is not equal");
			Assert().IsTrue(modelThree->getModelInfo()->zMin == expZMin, L"zMax is not equal");
			Assert().IsTrue(modelThree->getModelInfo()->zWidth == expZWidth, L"zWidth is not equal");

			Assert().IsTrue(modelThree->getModelInfo()->modelArr[0] == 'X',L"Address 0 not equal");
			Assert().IsTrue(modelThree->getModelInfo()->modelArr[1] == 'Y',L"Address 1 not equal");
			Assert().IsTrue(modelThree->getModelInfo()->modelArr[2] == 'Z',L"Address 2 not equal");

			delete modelOne;
			delete modelTwo;
			delete modelThree;

			delete db;
		}

		TEST_METHOD(testDatabaseFileIOStreams)
		{
			//This is pretty much a giant regurgitation of testDatabaseAddGetModel
			//with the exception that before the models are loaded the database
			//is reinitialized and is loaded from a file.

			//These models really should have a more unique quality to them but
			//in interest of time I will edit them later. -Andy
			
			//Really the only thing necessary to test here is that the files where loaded.
			//This can be done simply by checking the MUID, the rest is tested in
			//modelClassTest.cpp->fileIOTest
			sf_db *db = new sf_db;
			Model *modelOne, *modelTwo, *modelThree;
			modelOne = new Model("MD.","Punish","Me", "Please", "Sr", "Male","Owww@drPain.com");
			modelTwo = new Model("Mr.","Joe","F", "Dirt", "Jr", "Male","DirtJoe@email.com");
			modelThree = new Model("Dr.","Gordon","P", "Freeman", "I", "Male","gordon@valve.com");

			modelOne->setPersonUID(111111L);
			modelOne->setModelUID(222222L); 

			modelTwo->setPersonUID(333333L);
			modelTwo->setModelUID(444444L); 

			modelThree->setPersonUID(555555L);
			modelThree->setModelUID(666666L); 

			modelOne->initModelArray();
			modelTwo->initModelArray();
			modelThree->initModelArray();

			Assert().IsTrue(db->addModelToDatabase(modelOne) == SF_STS_OK, L"Failed to add model to database.");
			Assert().IsTrue(db->addModelToDatabase(modelTwo) == SF_STS_OK, L"Failed to add model to database.");
			Assert().IsTrue(db->addModelToDatabase(modelThree) == SF_STS_OK, L"Failed to add model to database.");
			
			wchar_t* buffer;

			// Gets the current working directory  
			if( (buffer = _wgetcwd( NULL, 0 )) == NULL )
				//perror( "_getcwd error" );-Should Assert
				Assert().Fail(L"Failed to get current working directory");
			else
			{
				Logger().WriteMessage( L"Path:");
				Logger().WriteMessage(buffer);
			}
			
			//append full file path onto temp
			wchar_t temp[200] = L"";
			wcscat_s(temp, buffer);
			wcscat_s(temp, L"\\testdatabase\\");
			Logger().WriteMessage(L"\n");
			Logger().WriteMessage(temp);

			DWORD ftyp = GetFileAttributesW(temp);
			delete[] buffer;

			//Creates a folder if it does not exist
			if (ftyp == INVALID_FILE_ATTRIBUTES)
			{
				Logger().WriteMessage(L"\ncreating directory"); //may not exist
				_wmkdir(temp);
			}
			else if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
			{
				Logger().WriteMessage(L"\ndirectory found"); //this is a directory
			}
			
			//convert from wide char to narrow char array
			char ch[200];
			char DefChar = ' ';
			WideCharToMultiByte(CP_ACP,0,temp,-1, ch,200,&DefChar, NULL);
    
			//A std:string  using the char* constructor.
			std::string ss(ch);

			Logger().WriteMessage(L"\nPath is:");
			Logger().WriteMessage(ss.c_str());

			Assert().IsTrue(db->saveDatabase(ss) == SF_STS_OK,L"Failed to save to database");

			sf_db *db2 = new sf_db();

			Assert().IsTrue(db2->loadDatabase(ss) == SF_STS_OK,L"Failed to load to database");
			//The following asserts that the model exists... and that the UID's are equal
			Assert().IsTrue(db2->getModel(modelOne->getModelUID())->getModelUID()  == modelOne->getModelUID(),L"Loaded Model UID Not Equal"); 
			Assert().IsTrue(db2->getModel(modelTwo->getModelUID())->getModelUID()  == modelTwo->getModelUID(),L"Loaded Model UID Not Equal"); 
			Assert().IsTrue(db2->getModel(modelThree->getModelUID())->getModelUID()  == modelThree->getModelUID(),L"Loaded Model UID Not Equal"); 
			
			Model *modelOut = db2->getModel(modelThree->getModelUID());
			char str[200]; 
			sprintf_s(str,200,"\nRetrieved MUID: %d\n", modelOut->getModelUID());
			Logger().WriteMessage(str);
			delete modelOne;
			delete modelTwo;
			delete modelThree;

			delete db;
			delete db2;
		}


	};
}