/*
*Priority number if assigned, followed by the TODO

* Class sf_sdk_session
* (Medium) Save Snapshot


*
* Class Model_Builder
* Make a process vertice method... and build the model. (Major milestone).
* Save Snapshot... (to be implemented in sf_session first)... Save the image of the last frame used to build.
* 
* TESTS TODO
*
* Class Model
* Add params to keep track of comparison tracking. (Figure out the params later)
* Add return fail status and do not save, if initModelArr has not been called.

*Classes that are Finished and Tested
*sf_tr_func (Well Should add more testing for modelspace coords... But should become self-evident if there is a problem).
*sf_db (I feel confident this is done -Andy)
*sf_util (this class is tested in testDatabaseFileIOStreams and works)
*sf_tr_test (exist as a wrapper call to the tr_func for test dll.)

*classes to be worked on.
*sf_controller, contains main program flow and holds the globals. Interfaces with UI.
*sf model builder... Fully constructs the model, responsible to make sure all neccesary vars are filled.
*	Will also be the fondation for the comparitor... consider moving globals/global functions to own cpp file.
*	That is a matter of making a header/cpp file and a #include.
*	Note that the implementation should be in the cpp file so it is compiled to the .lib for testing.
*sf_comparitor... Not implemented, finish model_builder first. (can be implemented PDQ)
*	Allow for multiple instances.
*/