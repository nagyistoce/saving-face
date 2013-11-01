#include "stdafx.h"
#include "CppUnitTest.h"
#include "sf_model.h"

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



		Model *model;
		//For Best Practices use the test method initializers / cleanup.
		//Not done here
		//There are a lot of other tidbits for testing not yet used.
		
		//This is potentially bad juju
		//There may be other attributes not being set by setting a default constructor.
		//Also this may not even be being called.
		modelClassTest()
		{
			model = 0;
		}


		//Same goes for the destructor
		~modelClassTest()
		{
			if(model) delete model;
		}

		//Use the Logger mechanism to print out results.

		TEST_METHOD(defaultConstructorTest)
		{
			if(model != nullptr)
				delete model;
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
			if(model != nullptr)
				delete model;
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
			if(model != nullptr)
				delete model;
			model = new Model("Shannon","Elizabeth","feMale","Hiddy@Hoe.com");
			model_info  = model->getModelInfo();
			person_info = model->getPersonInfo();
			Assert().IsTrue(person_info->firstName == "Shannon");
			Assert().IsTrue(person_info->lastName == "Elizabeth");
			Assert().IsTrue(person_info->emailAddress == "Hiddy@Hoe.com");
			Assert().IsTrue(person_info->gender == "female");
			if(model != nullptr)
				delete model;
			model = nullptr;
		}

		TEST_METHOD(fullNameConstructorTest)
		{
			//TODO
			Assert().Fail();
		}

		TEST_METHOD(fullySpecifiedConstructorTest)
		{
			//TODO
			Assert().Fail();
		}

		TEST_METHOD(constructModelArrayTest)
		{
			//TODO implement and test
			//SF::SF_STS sts = model->initModelArray();
			Assert().Fail();
		}
		

		TEST_METHOD(TestSettersAndGetters)
		{
			if(model == nullptr)
				model = new Model();
			
			
			//Test the following via the getters
			model->setName("Mr.","Bob","Jo-ann","Barker", "III");
			//TODO Test
			model->setEmail("BogusPerson@Bogus.net");
			//TODO Test
			model->setGender("Male");
			//TODO Test Success
			model->setGender("None");
			//TODO Test Fail
			
			//Test these too
			model->getConcatenatedName();
			model->getFileVersionName();
			model->getModelInfo();
			model->getPersonInfo();

			//included in test defaultConstructorTest
			//model->setDefaultParameters()

			
			//TODO Test Name, Email, and Gender Setters and Getters

			//TODO Test Model Parameter Getters and Setters
			//Make Sure it returns an error code if the Model has already been initialized

			//TODO Test concatenated Name Getters
			Assert().Fail();
		}

		TEST_METHOD(TestFileIOStreams)
		{
			if(model == nullptr)
				model = new Model();
			
			//TODO test file export;

			//TODO test file import;

			//TODO destroy created files after test;

			Assert().Fail();
		}


		TEST_METHOD(TestModelArrModifyAndRead)
		{
			//Test Read only and read/write
			if(model == nullptr)
				model = new Model();

			//TODO test model Arr(increment points, readback points, total model value etc)

			Assert().Fail();
		}
	};
}