#ifndef _SF_TYPE_DEFS
#define _SF_TYPE_DEFS
#include <string>

namespace SF
{

	//A name or part of a name of a person
	#define SF_NAME std::string

	//An email address
	#define SF_EMAIL std::string

	//Describes a real-world bound
	//Example: SF_BOUND xMin = -0.25 //might mean xMin = 0.25 m to the left
	#define SF_BOUND float 

	//Describes a real-world delta value
	//Example: SF_DELTA x = 0.0025 //might mean 2.5 mm 
	#define SF_DELTA float

	//Describes a dimensionless offset of a model array
	//Example:	int arr[x,y,z]
	//			SF_ARR_OFFSET xOffset = y * z, yOffset = z;
	#define SF_ARR_OFFSET int

	//Describes the dimensionless length of an n-dimentional array
	//Example:	SF_ARR_WIDTH x = 5, y = 10; 
	//			int arr[x,y]
	#define SF_ARR_WIDTH int

	//Return status of an Operation
	//1 indicates Success
	//0 or less indicates a failure
	//See further defs for failure types
	#define SF_STS int
}


#endif // !_SF_TYPE_DEFS
