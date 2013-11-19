#include "stdafx.h"
#include "CppUnitTest.h"
#include "sf_model.h"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SF;
namespace SavingFaceTest
{
	TEST_CLASS(modelClassTest)
	{
	public:
		/*Testing TODO LIST
		* Finish testing full name, and fully implemented constructors
		* Test Array construction both default, custom and with bogus values.
		*		(Report Array Sizes through the logger)
		* Test File input and output
		* Test read and write to array. Test for roll over behavior.
		*/


		TEST_METHOD(defaultConstructorTest)
		{
			Model *model;
			model = new Model();
			Model::Model_Info  const *model_info  = model->getModelInfo();
			Model::Person_Info const *person_info = model->getPersonInfo();
			Assert().AreEqual(model_info->xMin, SF_DEFAULT_XMIN);
			Assert().AreEqual(model_info->xMax, SF_DEFAULT_XMAX);
			Assert().AreEqual(model_info->yMin, SF_DEFAULT_YMIN);
			Assert().AreEqual(model_info->yMax, SF_DEFAULT_YMAX);
			Assert().AreEqual(model_info->zMin, SF_DEFAULT_ZMIN);
			Assert().AreEqual(model_info->zMax, SF_DEFAULT_ZMAX);
			Assert().AreEqual(model_info->deltaX, SF_DEFAULT_DELTAX);
			Assert().AreEqual(model_info->deltaY, SF_DEFAULT_DELTAY);
			Assert().AreEqual(model_info->deltaZ, SF_DEFAULT_DELTAZ);
			Assert().AreEqual(model_info->xWidth, (SF_ARR_WIDTH)(((SF_DEFAULT_XMAX - SF_DEFAULT_XMIN)) / SF_DEFAULT_DELTAX));
			Assert().AreEqual(model_info->yWidth, (SF_ARR_WIDTH)(((SF_DEFAULT_YMAX - SF_DEFAULT_YMIN)) / SF_DEFAULT_DELTAY));
			Assert().AreEqual(model_info->zWidth, (SF_ARR_WIDTH)(((SF_DEFAULT_ZMAX - SF_DEFAULT_ZMIN)) / SF_DEFAULT_DELTAZ));
			Assert().IsTrue(person_info->salutation == "");
			Assert().IsTrue(person_info->firstName == "");
			Assert().IsTrue(person_info->lastName == "");
			Assert().IsTrue(person_info->emailAddress == "");
			Assert().IsTrue(person_info->gender == "");
			delete model;
			model = nullptr;
		}

		TEST_METHOD(shortConstructorTest)
		{
			Model *model;
			model = new Model("Bob","Barker", "Male");
			Model::Model_Info  const *model_info  = model->getModelInfo();
			Model::Person_Info const *person_info = model->getPersonInfo();
			Assert().AreEqual(model_info->xMin, SF_DEFAULT_XMIN);
			Assert().AreEqual(model_info->xMax, SF_DEFAULT_XMAX);
			Assert().AreEqual(model_info->yMin, SF_DEFAULT_YMIN);
			Assert().AreEqual(model_info->yMax, SF_DEFAULT_YMAX);
			Assert().AreEqual(model_info->zMin, SF_DEFAULT_ZMIN);
			Assert().AreEqual(model_info->zMax, SF_DEFAULT_ZMAX);
			Assert().AreEqual(model_info->deltaX, SF_DEFAULT_DELTAX);
			Assert().AreEqual(model_info->deltaY, SF_DEFAULT_DELTAY);
			Assert().AreEqual(model_info->deltaZ, SF_DEFAULT_DELTAZ);
			Assert().AreEqual(model_info->xWidth, (SF_ARR_WIDTH)(((SF_DEFAULT_XMAX - SF_DEFAULT_XMIN)) / SF_DEFAULT_DELTAX));
			Assert().AreEqual(model_info->yWidth, (SF_ARR_WIDTH)(((SF_DEFAULT_YMAX - SF_DEFAULT_YMIN)) / SF_DEFAULT_DELTAY));
			Assert().AreEqual(model_info->zWidth, (SF_ARR_WIDTH)(((SF_DEFAULT_ZMAX - SF_DEFAULT_ZMIN)) / SF_DEFAULT_DELTAZ));
			Assert().IsTrue(person_info->salutation == "");
			Assert().IsTrue(person_info->firstName == "Bob");
			Assert().IsTrue(person_info->lastName == "Barker");
			Assert().IsTrue(person_info->emailAddress == "");
			Assert().IsTrue(person_info->gender == "male");
			delete model;
			model = new Model("Shannon","Elizabeth","feMale","Hiddy@Hoe.com");
			model_info  = model->getModelInfo();
			person_info = model->getPersonInfo();
			Assert().IsTrue(person_info->firstName == "Shannon");
			Assert().IsTrue(person_info->lastName == "Elizabeth");
			Assert().IsTrue(person_info->emailAddress == "Hiddy@Hoe.com");
			Assert().IsTrue(person_info->gender == "female");
			delete model;
			model = nullptr;
		}

		TEST_METHOD(fullNameConstructorTest)
		{
			Model *model;
			model = new Model("Mr.","Bob","Bernadine","Barker","Jr","Male","ThePriceIsWrong@B3.com");
			Model::Model_Info  const *model_info  = model->getModelInfo();
			Model::Person_Info const *person_info = model->getPersonInfo();
			Assert().AreEqual(model_info->xMin, SF_DEFAULT_XMIN);
			Assert().AreEqual(model_info->xMax, SF_DEFAULT_XMAX);
			Assert().AreEqual(model_info->yMin, SF_DEFAULT_YMIN);
			Assert().AreEqual(model_info->yMax, SF_DEFAULT_YMAX);
			Assert().AreEqual(model_info->zMin, SF_DEFAULT_ZMIN);
			Assert().AreEqual(model_info->zMax, SF_DEFAULT_ZMAX);
			Assert().AreEqual(model_info->deltaX, SF_DEFAULT_DELTAX);
			Assert().AreEqual(model_info->deltaY, SF_DEFAULT_DELTAY);
			Assert().AreEqual(model_info->deltaZ, SF_DEFAULT_DELTAZ);
			Assert().AreEqual(model_info->xWidth, (SF_ARR_WIDTH)(((SF_DEFAULT_XMAX - SF_DEFAULT_XMIN)) / SF_DEFAULT_DELTAX));
			Assert().AreEqual(model_info->yWidth, (SF_ARR_WIDTH)(((SF_DEFAULT_YMAX - SF_DEFAULT_YMIN)) / SF_DEFAULT_DELTAY));
			Assert().AreEqual(model_info->zWidth, (SF_ARR_WIDTH)(((SF_DEFAULT_ZMAX - SF_DEFAULT_ZMIN)) / SF_DEFAULT_DELTAZ));
			Assert().IsTrue(person_info->salutation == "Mr.");
			Assert().IsTrue(person_info->firstName == "Bob");
			Assert().IsTrue(person_info->middleName == "Bernadine");
			Assert().IsTrue(person_info->lastName == "Barker");
			Assert().IsTrue(person_info->suffix == "Jr");
			Assert().IsTrue(person_info->emailAddress == "ThePriceIsWrong@B3.com");
			Assert().IsTrue(person_info->gender == "male");
			delete model;
			model = nullptr;
		}

		TEST_METHOD(fullySpecifiedConstructorTest)
		{
			//TODO
			Assert().Fail(L"Not yet implemented");
		}

		TEST_METHOD(constructModelArrayTest)
		{
			//TODO implement and test
			//SF::SF_STS sts = model->initModelArray();
			//Important to test valid indices from zero to arrlength - 1
			Assert().Fail(L"Not Yet Implemented");
		}

		TEST_METHOD(TestSettersAndGetters)
		{
			Model *model;
			model = new Model();
		
			model->setName("Mr.","Bob","Jo-ann","Barker", "III");
			Assert().IsTrue(model->getSalutation() == "Mr.");
			Assert().IsFalse(model->getSalutation() == "Mr");
			Assert().IsTrue(model->getFirstName() == "Bob");
			Assert().IsFalse(model->getFirstName() == "bob");
			Assert().IsTrue(model->getMiddleName() == "Jo-ann");
			Assert().IsFalse(model->getMiddleName() == "Jo ann");
			Assert().IsTrue(model->getLastName() == "Barker");
			Assert().IsFalse(model->getLastName() == "Baker");
			Assert().IsTrue(model->getSuffix() == "III");
			Assert().IsFalse(model->getSuffix() == "II");
			
			model->setEmail("BogusPerson@Bogus.net");
			Assert().IsTrue(model->getEmail() == "BogusPerson@Bogus.net");

			model->setGender("MaLe");
			Assert().IsTrue(model->getGender() == "male");
			Assert().IsFalse(model->getGender() == "MaLe");
			
			Assert().IsTrue(model->getConcatenatedName() == "Mr. Bob Jo-ann Barker III");
			Assert().IsTrue(model->getFileVersionName() == "Mr._Bob_Jo-ann_Barker_III");
			
			delete model;
			model = nullptr;
		}

		TEST_METHOD(TestFileIOStreams)
		{
			Model *model;
			//I laughed hard at this line -Andy
			model = new Model("MD.","Punish","Me", "Please", "Sr", "Male","Owww@drPain.com");
			model->setPersonUID(56489742L);
			model->setModelUID(7986131546L);  //This value is getting truncated for some reason -Andy
			model->initModelArray();

			SF_MUID expMUID = model->getModelUID();
			
			model->getModelInfo()->modelArr[0] = 'A';
			model->getModelInfo()->modelArr[1] = 'B';
			model->getModelInfo()->modelArr[2] = 'C';
	
			ofstream *out = new ofstream("TestOutput.mdl");
			string exp = model->getConcatenatedName();

			SF_DELTA expDeltaX = model->getModelInfo()->deltaX;
			SF_BOUND expXMax = model->getModelInfo()->xMax;
			SF_BOUND expXMin = model->getModelInfo()->xMin;
			SF_ARR_OFFSET expXOffset = model->getModelInfo()->xOffset;
			SF_ARR_WIDTH expXWidth = model->getModelInfo()->xWidth;

			SF_DELTA expDeltaY = model->getModelInfo()->deltaY;
			SF_BOUND expYMax = model->getModelInfo()->yMax;
			SF_BOUND expYMin = model->getModelInfo()->yMin;
			SF_ARR_OFFSET expYOffset = model->getModelInfo()->yOffset;
			SF_ARR_WIDTH expYWidth = model->getModelInfo()->yWidth;

			SF_DELTA expDeltaZ = model->getModelInfo()->deltaZ;
			SF_BOUND expZMax = model->getModelInfo()->zMax;
			SF_BOUND expZMin = model->getModelInfo()->zMin;
			SF_ARR_WIDTH expZWidth = model->getModelInfo()->zWidth;

			model->streamToFile(out);
			out->flush();
			out->close();
			delete out;
			delete model;
			model = 0;
			
			ifstream *in = new ifstream("TestOutput.mdl");
			model = new Model();
			model->loadFromFile(in);
			in->close();
			Logger().WriteMessage(L"Expected Name: ");
			Logger().WriteMessage(exp.c_str());
			Logger().WriteMessage(L"\nReturned Name: ");
			Logger().WriteMessage(model->getConcatenatedName().c_str());

			Assert().AreEqual(exp, model->getConcatenatedName(),L"Names are not equal");
			
			for(int i = 0; i < 10; i++){
				char str[200];
				sprintf_s(str, 200, "\nAddress %d = %x", i, model->getModelInfo()->modelArr[i]);
				Logger().WriteMessage(str);
			}

			Assert().IsTrue(model->getModelInfo()->modelArr[0] == 'A',L"Address 0 not equal");
			Assert().IsTrue(model->getModelInfo()->modelArr[1] == 'B',L"Address 1 not equal");
			Assert().IsTrue(model->getModelInfo()->modelArr[2] == 'C',L"Address 2 not equal");
			
			//TODO
			//Test MUID PUID, All model Params
			Assert().IsTrue(model->getModelUID() == expMUID,L"MUID is not equal");
			Assert().IsTrue(model->getPersonUID() == 56489742L,L"PUID is not equal");
			Assert().IsTrue(model->getSalutation() == "MD.", L"Salutation is not equal");
			Assert().IsFalse(model->getSalutation() == "MD");
			Assert().IsTrue(model->getFirstName() == "Punish", L"First name is not equal");
			Assert().IsFalse(model->getFirstName() == "punish");
			Assert().IsTrue(model->getMiddleName() == "Me", L"Middle name is not equal");
			Assert().IsFalse(model->getMiddleName() == "me");
			Assert().IsTrue(model->getLastName() == "Please", L"Last name is not equal");
			Assert().IsFalse(model->getLastName() == "please");
			Assert().IsTrue(model->getSuffix() == "Sr", L"Suffix is not equal");
			Assert().IsFalse(model->getSuffix() == "Sr.");
			Assert().IsTrue(model->getGender() == "male", L"Gender is not equal");
			Assert().IsFalse(model->getGender() == "Male");
			Assert().IsTrue(model->getEmail() == "Owww@drPain.com", L"Email is not equal");

			Assert().IsTrue(model->getModelInfo()->deltaX == expDeltaX, L"deltaX is not equal");
			Assert().IsTrue(model->getModelInfo()->xMax == expXMax, L"xMin is not equal");
			Assert().IsTrue(model->getModelInfo()->xMin == expXMin, L"xMax is not equal");
			Assert().IsTrue(model->getModelInfo()->xOffset == expXOffset, L"xOffset is not equal");
			Assert().IsTrue(model->getModelInfo()->xWidth == expXWidth, L"xWidth is not equal");

			Assert().IsTrue(model->getModelInfo()->deltaY == expDeltaY, L"deltaY is not equal");
			Assert().IsTrue(model->getModelInfo()->yMax == expYMax, L"yMin is not equal");
			Assert().IsTrue(model->getModelInfo()->yMin == expYMin, L"yMax is not equal");
			Assert().IsTrue(model->getModelInfo()->yOffset == expYOffset, L"yOffset is not equal");
			Assert().IsTrue(model->getModelInfo()->yWidth == expYWidth, L"yWidth is not equal");

			Assert().IsTrue(model->getModelInfo()->deltaZ == expDeltaZ, L"deltaZ is not equal");
			Assert().IsTrue(model->getModelInfo()->zMax == expZMax, L"zMin is not equal");
			Assert().IsTrue(model->getModelInfo()->zMin == expZMin, L"zMax is not equal");
			Assert().IsTrue(model->getModelInfo()->zWidth == expZWidth, L"zWidth is not equal");

			delete model;
			model = nullptr;

			//Assert().Fail(L"not finished");
		}


		TEST_METHOD(TestModelArrModifyAndRead)
		{
			//Test Read only and read/write
			Model *model;
			model = new Model();

			//TODO test model Arr(increment points, readback points, total model value etc)
			delete model;
			model = nullptr;
			Assert().Fail(L"Test Not Implemented");
		}
	};
}