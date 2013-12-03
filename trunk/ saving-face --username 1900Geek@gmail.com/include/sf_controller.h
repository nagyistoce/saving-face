#ifndef _SF_CONTROLLER
#define _SF_CONTROLLER
//Something strange is going on with the includes.
#include <windows.h>
#include "sf_db.h"
#include "sf_model.h"
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
	
	//Return -1 if required fields are not initialized.
	SF_MUID createModel(SF_NAME const salutation, SF_NAME const firstName, SF_NAME const middleName, SF_NAME const lastName, SF_NAME const suffix,SF_GENDER const gender,  SF_EMAIL const email);

	//Opens a video feed to take the picture.
	SF_STS takeSnapshot(SF_MUID modelId);

	//Quick implementation of save and load database
	//probably want to add an argument for the path
	SF_STS loadDatabase();
	SF_STS saveDatabase();
	
	//Take the photo.
	void pressShutter();
	
	//Close the Snapshot video feed
	void snapshotFinished();

	//returns the path of the photo.
	string getSnapshotPath(SF_MUID modelID);

	SF_STS buildModel(SF_MUID modelID);
	
	
	
	//Contains functionality to parse a text command.
	//Mostly for debug
	SF_STS command(string textCommand);

	//Initialization outside of constructor, means constructor will never fail.
	//If mode = "", default initialization
	//Set up macros for other special modes.
	//Debug, verbose, alternative algorithms, playback mode(no camera)... etc
	SF_STS init(string mode = "");

	//Add Functions as needed

private: 
	sf_db *db;
	sf_model_builder *mBuilder;
	SF_Session *session;
};

struct bob
{
	sf_controller *controller;
	SF_MUID modelId;
};

void threadStartSnapshot(bob *theBob);

#endif
