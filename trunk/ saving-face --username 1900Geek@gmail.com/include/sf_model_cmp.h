#include <Windows.h>
#include "sf_defs.h"
#include "sf_model.h"
#include "sf_db.h"
#include "sf_model_builder.h"
#include <vector>


using namespace SF;
namespace SF
{	
	class sf_model_cmp
	{
	public:
		
		struct cmp_results
		{
			vector<string> names;
			vector<float> scores;
			//vector<int> scores;
			vector<string> imagePaths;
		};

		sf_model_cmp(sf_db *db, SF_Session *session);
		~sf_model_cmp();

		//temp until call back is added
		cmp_results *compare();

		//Temp
		vector<int> sums;
		


	private:
		sf_db *db;
		Model *model;
		SF_Session *session;
		sf_model_builder *builder;
		Model **models;
		int numModels;
		SF_STS getModelReferences();
	};
}