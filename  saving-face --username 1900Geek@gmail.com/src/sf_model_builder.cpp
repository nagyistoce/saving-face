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

	SF_UID_TYPE sf_model_builder::generateUID()
	{
		time_t t;
		time(&t);
		return (long)t;
	}

	SF_MUID sf_model_builder::addNewModel()
	{
		Model *model = new Model();
		SF_UID_TYPE uid = generateUID();
		model->setModelUID(uid);
		model->setPersonUID(uid);
		model->initModelArray();
		temp_db.addModelToDatabase(model);
		return uid;
	}


	SF_TR_MATRIX* getTr(SF_YPR* ypr, SF_R3_COORD* trCoord)
	{
		SF_TR_MATRIX *tr;
		calculateTRMatrix(*tr, *trCoord, *ypr);
		return tr;
	}

	void processVertex(SF_R3_COORD& coord)
	{

	}

	void onNewFrame(int frameNumber)
	{

	}

	Model *sf_model_builder::getModel(SF_MUID muid)
	{
		return temp_db.getModel(muid);
	}

	SF_STS sf_model_builder::deleteModel(SF_MUID muid)
	{
		return temp_db.deleteModelFromDatabase(muid);
	}

}