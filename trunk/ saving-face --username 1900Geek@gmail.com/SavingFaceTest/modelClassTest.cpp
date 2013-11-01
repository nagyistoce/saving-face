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
			Model::Model_Info  model_info = model->getModelInfo();
			Model::Person_Info  person_info = model->getPersonInfo();
			Assert().AreEqual(model_info.xMin, SF_DEFAULT_XMIN);
			Assert().AreEqual(model_info.xMax, SF_DEFAULT_XMAX);
			Assert().AreEqual(model_info.yMin, SF_DEFAULT_YMIN);
			Assert().AreEqual(model_info.yMax, SF_DEFAULT_YMAX);
			Assert().AreEqual(model_info.zMin, SF_DEFAULT_ZMIN);
			Assert().AreEqual(model_info.zMax, SF_DEFAULT_ZMAX);
			Assert().AreEqual(model_info.deltaX, SF_DEFAULT_DELTAX);
			Assert().AreEqual(model_info.deltaY, SF_DEFAULT_DELTAY);
			Assert().AreEqual(model_info.deltaZ, SF_DEFAULT_DELTAZ);
			Assert().AreEqual(model_info.xWidth, (SF_ARR_WIDTH)(((SF_DEFAULT_XMAX - SF_DEFAULT_XMIN)) / SF_DEFAULT_DELTAX));
			Assert().AreEqual(model_info.yWidth, (SF_ARR_WIDTH)(((SF_DEFAULT_YMAX - SF_DEFAULT_YMIN)) / SF_DEFAULT_DELTAY));
			Assert().AreEqual(model_info.zWidth, (SF_ARR_WIDTH)(((SF_DEFAULT_ZMAX - SF_DEFAULT_ZMIN)) / SF_DEFAULT_DELTAZ));
			Assert().IsTrue(person_info.salutation == "");
			Assert().IsTrue(person_info.firstName == "");
			Assert().IsTrue(person_info.lastName == "");
			Assert().IsTrue(person_info.emailAddress == "");
			Assert().IsTrue(person_info.gender == "");
		}


		//TODO Test Alternate Constructors

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


		TEST_METHOD(testChangeModelParameters)
		{
			Assert().Fail();
		}

		TEST_METHOD(TestModelArrModifyAndRead)
		{
			if(model == nullptr)
				model = new Model();

			//TODO test model Arr(increment points, readback points, total model value etc)

			Assert().Fail();
		}
	};
}