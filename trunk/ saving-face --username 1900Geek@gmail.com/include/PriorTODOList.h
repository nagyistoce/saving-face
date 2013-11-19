/*
*Priority number if assigned, followed by the TODO
* Class sf_db
* (High) SF_STS saveDatabase(string path);
*		If a model returns a fail status on save... go back and delete the file.
* (High) SF_STS loadDatabase(string path);
* (Low)  SF_STS deleteModelFromDatabase(SF_MUID *modelID);
* 
* I will add more as I go through, but these are good to start on.
* 
* TESTS TODO
* (Medium) TEST_METHOD(TestModelArrModifyAndRead)
* (Low)    TEST_METHOD(fullySpecifiedConstructorTest)
*
* Class Model
* Add params to keep track of comparison tracking. (Figure out the params later)
* Add return fail status and do not save, if initModelArr has not been called.
* 
* Class Model_Builder
* Un-implemented methods... High priority
* Actually build the model... High priority...
* Save Video Option... (to be implemented in sf_session first)
* Save Snapshot... (to be implemented in sf_session first)... Save the image of the last frame used to build.


*Classes that are Finished and Tested
*sf_tr_func (Well Should add more testing for modelspace coords).
*/