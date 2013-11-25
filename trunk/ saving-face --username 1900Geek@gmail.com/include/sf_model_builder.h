#ifndef _SF_MODEL_BUILDER
#define _SF_MODEL_BUILDER

#include "sf_sdk_session.h"
#include "sf_tr_func.h"
#include "sf_defs.h"
#include "sf_model.h"
#include "sf_db.h"

using namespace SF;
namespace SF
{
	//This classes responsibility, is to ensure proper instantiation and initialization of a model
	//And to apply coordinates to the model until X number of Frames, or told to stop.
	//It should then be able to rerun the data (From recorded video) used to create the model to give a proxy for a good score.
	//Need to add the ability to hold on to those scores in the model class.
	//This should call a sdk loop to accomplish this task.
	//In order to prevent unnecessary code replication, it should call a predefined function in the sf_sdk_session
	//class and pass in a recieving function as an argument, and an argument to record the video with a filename.

	
	class sf_model_builder
	{


	public:

		sf_model_builder(void);
		~sf_model_builder(void);

		//Generate a unique ID
		//Note that some random number generators will not repeat until over a billion calls
		//Or just take the date and time down to the second for person and the second + 1 for a model.
		//Example 20131101143806 and 20131101143807
		SF_UID_TYPE generateUID();

		//Make a new model
		//Adds it to the current model list
		//This is the only place a model constructor should be called
		//With the exception of test methods
		//This will add the model to the local database simultaniously 
		SF_MUID addNewModel();

		//Ideally this would be in the Model Database.
		SF_STS deleteModel(SF_MUID muid);

		//Returns a reference to the model class.
		//Eleminates the need for wrapper functions
		//Required because a model should only be added to
		//the database after a succesful build.
		Model *getModel(SF_MUID muid);

		//Contains the loop to the camera
		//Include options to save video
		//Save model to disk when finished
		Model buildModel(SF_MUID muid);//Working on param list

	private:
		//temp_db holds the working model while being built, private instance
		//actual_db holds a reference to the actual database.
		sf_db temp_db, *actual_db; 
	};
}
#endif