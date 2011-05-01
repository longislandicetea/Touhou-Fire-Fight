#include "MoogeUtility.h"
#include <string.h>

//Convert an array style vector to structure style.
VECTORFS ConvertVectorA2S(VECTORFA VectorArrayIn)
{
	VECTORFS VectorStructOut;
	//Taking risk. But this would be faster.
	memcpy(&VectorStructOut, VectorArrayIn, sizeof(VECTORFS));
	return VectorStructOut;
}

//Convert an structure style vector to array style.
void ConvertVectorS2A(VECTORFS VectorStructIn, VECTORFA VectorArrayOut)
{
	//Taking risk. But this would be faster.
	memcpy(VectorArrayOut, &VectorStructIn, sizeof(VECTORFS));
}

//Convert an array style 3ub color to structure style.
COLOR3UBS ConvertColor3ubA2S(COLOR3UBA ColorArrayIn)
{
	COLOR3UBS ColorStructOut;
	//Taking risk. But this would be faster.
	memcpy(&ColorStructOut, ColorArrayIn, sizeof(COLOR3UBS));
	return ColorStructOut;
}

//Convert a structure style 3ub color to array style.
void ConvertColor3ubS2A(COLOR3UBS ColorStructIn, COLOR3UBA ColorArrayOut)
{
	//Taking risk. But this would be faster.
	memcpy(ColorArrayOut, &ColorStructIn, sizeof(COLOR3UBS));
}

//Convert an array style 4ub color to structure style.
COLOR4UBS ConvertColor4ubA2S(COLOR4UBA ColorArrayIn)
{
	COLOR4UBS ColorStructOut;
	//Taking risk. But this would be faster.
	memcpy(&ColorStructOut, ColorArrayIn, sizeof(COLOR4UBS));
	return ColorStructOut;
}

//Convert a structure style 4ub color to array style.
void ConvertColor4ubS2A(COLOR4UBS ColorStructIn, COLOR4UBA ColorArrayOut)
{
	//Taking risk. But this would be faster.
	memcpy(ColorArrayOut, &ColorStructIn, sizeof(COLOR4UBS));
}