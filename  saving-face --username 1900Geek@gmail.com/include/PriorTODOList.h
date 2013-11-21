/*
*Priority number if assigned, followed by the TODO
* Class sf_db
* (Low)  SF_STS deleteModelFromDatabase(SF_MUID *modelID);


***** Make sf_util.cpp
* Extract the code used in databaseFunctionsTest to make functions
string getFullPath(string partialPath)
string makeDirectory(string Path)


* Class sf_sdk_session
* (High) Method to get depth vertices data
* (High) Method to convert YPR to a depth vertice
* (Medium) Save video
* (Medium) Save Snapshot
* I will add more as I go through, but these are good to start on.
* 
* TESTS TODO
*
* Class Model
* Add params to keep track of comparison tracking. (Figure out the params later)
* Add return fail status and do not save, if initModelArr has not been called.
* 
* Class Model_Builder
* Un-implemented methods... High priority (Most depend on sf_sdk functionality)
* Actually build the model... High priority...
* Save Video Option... (to be implemented in sf_session first)
* Save Snapshot... (to be implemented in sf_session first)... Save the image of the last frame used to build.


*Classes that are Finished and Tested
*sf_tr_func (Well Should add more testing for modelspace coords... But should become self-evident if there is a problem).
*/