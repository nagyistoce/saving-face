#include "stdafx.h"
#include "CppUnitTest.h"
#include "sf_model_builder.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SavingFaceTest
{

	TEST_CLASS(modelBuilderTest)
	{
		
	public:
		TEST_METHOD(modelBuilderGenUIDTest)
		{
			//Look at results by hand.
			//Unlikely to break
			//Success if all are different.
			//Note that these are accurate to one second.
			//As long as you never make two models in the same second
			//They will be unique
			SF::sf_model_builder builder;
			int i = 0;
			while(i < 10)
			{
				_sleep(1000);//Sleep for 1 second.
				i++;
				long uid = builder.generateUID();
				char *str = new char[200];
				sprintf(str, "MUID:: %d\n", uid);
				Logger::WriteMessage(str);
			}
		}

		TEST_METHOD(modelBuilderInstantiateModel)
		{
			sf_model_builder *modelBuilder = new sf_model_builder();
			SF_MUID muid = modelBuilder->addNewModel();
			if(muid <= 0)
			Assert().Fail(L"Failed to instantiate model");
			Model *model = modelBuilder->getModel(muid);
			Assert().IsNotNull(model,L"Failed to retrieve instance");
			char *str = new char[200];
			sprintf(str, "Generated a Model With Model ID:: %d\n", muid);
			Logger().WriteMessage(str);
			model->setName("Dr.","","","Who","dat");
			string s = model->getConcatenatedName();
			sprintf(str, "Model name:: %s\n", s.c_str());
			Logger().WriteMessage(str);
			SF_PUID puid = model->getPersonInfo()->puid;
			sprintf(str, "Model Person ID:: %d\n", puid);
			Logger().WriteMessage(str);
			Assert().AreEqual(muid, puid, L"Model MUID != PUID");
		}

	};
}