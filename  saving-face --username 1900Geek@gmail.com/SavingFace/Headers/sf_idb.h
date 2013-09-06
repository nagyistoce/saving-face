#include <vector>
#include <memory>
#include <string>
#include "sf_icontroller.h"

#ifndef _SF_IDB

using namespace std;
namespace SF
{

	#ifndef _SF_TYPES

		struct SF_VERTEX
		{
			float x,y,z;
		};

		struct SF_VERTICES
		{
			SF_VERTEX *vertices;
			int length;
		};


		typedef uint32_t SF_STATUS;//1 for return status ok. <=0 indicates an error
		typedef _ULonglong  *SF_PID;//A unique Person ID::Persistant between sessions, Ideally should be hashable
		typedef vector<SF_PID> *SF_PIDS;//List of all available PIDs
		typedef wstring  *SF_NAME;//A name or part of a name
		typedef wstring  *SF_EMAIL;//An email address
		typedef int32_t  *SF_EXPRESSION;//A named expression
		typedef vector<SF_EXPRESSION>  *SF_EXPRESSIONS;//List of All Available PIDs
	#endif // !_SF_TYPES

	class sf_idb
	{
	public:
		virtual const shared_ptr<SF_PIDS> getPIDS() {return nullptr;};
	
		//Name/Email Functions Should Not Fail;
		//They Should Return L"" if a name does not exists
		//Names should allow the Full UTF-16 Character set
		
		//Retrieve the person's first name
		virtual const shared_ptr<SF_NAME> getFirstName(const SF_PID person) {return nullptr;};
		//Retrieve the person's middle name
		virtual const shared_ptr<SF_NAME> getMiddleName(const SF_PID person) {return nullptr;};
		//Retrieve the person's last name
		virtual const shared_ptr<SF_NAME> getLastName(const SF_PID person) {return nullptr;};
		//Retrieve the person's preffered prefix. e.g. Dr., Mr., Mrs., etc
		virtual const shared_ptr<SF_NAME> getNamePrefix(const SF_PID person) {return nullptr;};
		//Retrieve the person's suffix. e.g. Jr., Sr., III, etc
		virtual const shared_ptr<SF_NAME> getNameSuffix(const SF_PID person) {return nullptr;};
		//Retrieve the person's full name
		virtual const shared_ptr<SF_NAME> getFullName(const SF_PID person) {return nullptr;};
		//Retrieve the person's email address
		virtual const shared_ptr<SF_EMAIL> getEmail(const SF_PID person) {return nullptr;};

		//Retrieve the vertex model for a person's particular expression
		//Returns nullptr if the expression does not exist
		virtual const shared_ptr<SF_VERTICES> getExpression(const SF_PID person, const SF_EXPRESSION){return nullptr;};
	
	protected:
		//Set the person's first name
		virtual const SF_STATUS setFirstName(const SF_PID person, const SF_NAME firstName) {return 0;};
		//Set the person's middle name
		virtual const SF_STATUS setMiddleName(const SF_PID person, const SF_NAME middleName) {return 0;};
		//Set the person's last name
		virtual const SF_STATUS setLastName(const SF_PID person,const SF_NAME lastName) {return 0;};
		//Set the person's preffered prefix e.g. Dr., Mr., Mrs., etc
		virtual const SF_STATUS setNamePrefix(const SF_PID person,const SF_NAME salutation) {return 0;};
		//Set the person's suffix. e.g. Jr., Sr., III, etc
		virtual const SF_STATUS setNameSuffix(const SF_PID person,const SF_NAME suffix) {return 0;};

		//Set the person's email address
		virtual const SF_STATUS setEmail(const SF_PID person,const SF_EMAIL email) {return 0;};


		//Create a new person and return the PID
		virtual const shared_ptr<SF_PIDS> createNewPerson() {return nullptr;};

		//Delete a person from the database
		virtual const SF_STATUS deletePerson(const SF_PID person,const bool deleteFile) {return 0;};

		//Add an expression model to a person
		virtual const SF_STATUS addPersonModel(const SF_PID person,const SF_EXPRESSION expressionID,const SF_VERTICES verticesData, const bool overwiteExpression);

		//Give Access to protected methods
	    friend class sf_icontroller;
	};
}

#endif // !_SF_IDB