#pragma once
//Something strange is going on with the includes.
//#include "sf_db.h"
//#include "sf_model.h"
#include "sf_sdk_session.h"
#include "sf_model_builder.h"

using namespace SF;
using namespace std;
class sf_controller
{
	//This class will be the one that the GUI attaches to
	//This class will own all instances of the primary components
	//And contains the flow control logic.

public:
	sf_controller(void);
	~sf_controller(void);
	
	//Contains functionality to parse a text command.
	SF_STS command(string textCommand);

	//Initialization outside of constructor, means constructor will never fail.
	//If mode = "", default initialization
	//Set up macros for other special modes.
	//Debug, verbose, alternative algorithms, playback mode(no camera)... etc
	SF_STS init(string mode = "");

	//Add Functions as needed

private: 
	//sf_db *db;
	sf_model_builder *mBuilder;
	SF_Session *session;
};

