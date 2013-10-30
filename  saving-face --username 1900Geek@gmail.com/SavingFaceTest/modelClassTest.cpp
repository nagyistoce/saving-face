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

		modelClassTest()
		{
			model = 0;
		}

		~modelClassTest()
		{
			if(model) delete model;
		}

#ifdef _DEBUG
		//Accesses private datamembers... Refactor to use getters
		//Better refactor Model to return a const struct with the datamembers
		//The later is neccesary to support a multi-model implementation
		//As well as fast access to parameters for transforms.
		TEST_METHOD(defaultConstructorTest)
		{
			model = new Model;
			Assert().AreEqual(model->xMin, SF_DEFAULT_XMIN);
			Assert().AreEqual(model->xMax, SF_DEFAULT_XMAX);
			Assert().AreEqual(model->yMin, SF_DEFAULT_YMIN);
			Assert().AreEqual(model->yMax, SF_DEFAULT_YMAX);
			Assert().AreEqual(model->zMin, SF_DEFAULT_ZMIN);
			Assert().AreEqual(model->zMax, SF_DEFAULT_ZMAX);
			Assert().AreEqual(model->deltaX, SF_DEFAULT_DELTAX);
			Assert().AreEqual(model->deltaY, SF_DEFAULT_DELTAY);
			Assert().AreEqual(model->deltaZ, SF_DEFAULT_DELTAZ);
			Assert().AreEqual(model->xWidth, (SF_ARR_WIDTH)(((SF_DEFAULT_XMAX - SF_DEFAULT_XMIN)) / SF_DEFAULT_DELTAX));
			Assert().AreEqual(model->yWidth, (SF_ARR_WIDTH)(((SF_DEFAULT_YMAX - SF_DEFAULT_YMIN)) / SF_DEFAULT_DELTAY));
			Assert().AreEqual(model->zWidth, (SF_ARR_WIDTH)(((SF_DEFAULT_ZMAX - SF_DEFAULT_ZMIN)) / SF_DEFAULT_DELTAZ));
			Assert().IsTrue(model->salutation == "");
			Assert().IsTrue(model->firstName == "");
			Assert().IsTrue(model->lastName == "");
			Assert().IsTrue(model->emailAddress == "");
			Assert().IsTrue(model->gender == "");
		}
#endif //_DEBUG

		//TODO Test Alternate Constructors

		TEST_METHOD(TestSettersAndGetters)
		{
			if(model == nullptr)
				model = new Model();
			
			//TODO Test Name, Email, and Gender Setters and Getters

			//TODO Test Model Parameter Getters and Setters
			//Make Sure it returns an error code if the Model has already been initialized

			//TODO Test concatenated Name Getters

		}

		TEST_METHOD(TestFileIOStreams)
		{
			if(model == nullptr)
				model = new Model();
			
			//TODO test file export;

			//TODO test file import;

			//TODO destroy created files after test;

			//TODO test model Arr(increment points, readback points, total model value etc)


		}
	};
}