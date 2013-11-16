#include "sf_model_builder.h"
#include <time.h>
namespace SF
{
	sf_model_builder::sf_model_builder(void)
	{
	}


	sf_model_builder::~sf_model_builder(void)
	{
	}

	long sf_model_builder::generateUID()
	{
		time_t t;
		time(&t);
		return t;
	}

}