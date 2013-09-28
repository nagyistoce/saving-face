#ifndef _SF_TYPE_DEFS
#define _SF_TYPE_DEFS
#include <string>
#include "pxcdefs.h"
namespace SF
{
	//A name or part of a name of a person
	typedef std::string SF_NAME; 

	//An email address
	 typedef std::string SF_EMAIL;

	//Describes a real-world bound
	//Example: SF_BOUND xMin = -0.25 //might mean xMin = 0.25 m to the left
	typedef float SF_BOUND;

	//Describes a real-world delta value
	//Example: SF_DELTA x = 0.0025 //might mean 2.5 mm 
	typedef float SF_DELTA;

	//Describes a dimensionless offset of a model array
	//Example:	int arr[x,y,z]
	//			SF_ARR_OFFSET xOffset = y * z, yOffset = z;
	typedef int SF_ARR_OFFSET;

	//Describes the dimensionless length of an n-dimentional array
	//Example:	SF_ARR_WIDTH x = 5, y = 10; 
	//			int arr[x,y]
	typedef int SF_ARR_WIDTH;

	//Return status of an Operation
	//1 indicates Success
	//0 or less indicates a failure
	//See further defs for failure types
	 typedef int SF_STS;

	//Defines a coordinate in 3D model space
	//Example SF_F32 x = -0.12f // Means -0.12 meters in the x direction from the origin
	 typedef float SF_F32;

	//Defines a unit vector scalar for a transform
	typedef float SF_SCALAR;

	//Defines a magnitude and direction to shift a coord in the real-world xyz plane
	//to put the point of rotation at the origin
	typedef PXCPoint3DF32 SF_TR_VECTOR; 

	
	//A struct containing a translational vector and a rotational matix
	struct SF_TR_MATRIX{			
			SF_TR_VECTOR trXYZ;
			SF_SCALAR trMatrix[9];	
	};

	//Defines what primitive we are storing
	//In this case a byte
	typedef char SF_MODEL_UNIT;
	
	//Defines a byte array that holds the model data
	typedef SF_MODEL_UNIT *SF_MODEL_ARR;

	//An offset into the model
	typedef int SF_MODEL_COORD;

	//A 3D Offset into the model.
	struct SF_MODEL_COORD3D{
		SF_MODEL_COORD x,y,z;
	};

	//Unique Personal Identifier
	//There is only one you
	//Labeling in good
	typedef long SF_PUID;

	//Unique Model Identifier
	//Potential to have more than one model
	//Associated with a Person
	typedef long SF_MUID;

	//Contains YAW PITCH and ROLL data
	struct SF_YPR{
		float yaw, pitch, roll;
	};

	//SUCCESS
	#define SF_STS_OK (1)
	//Failed memory allocation
	#define SF_STS_MEM_ALLOC_FAIL (-999)
}

#endif // !_SF_TYPE_DEFS
