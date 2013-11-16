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
			//Succeed if all are different.
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

	};
}