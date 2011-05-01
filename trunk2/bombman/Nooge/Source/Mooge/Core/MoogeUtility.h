#include "MoogeType.h"

//This file contain c-style utility functions for CMooge.
using namespace MoogeType;

//Convert an array style vector to structure style.
VECTORFS ConvertVectorA2S(VECTORFA VectorArrayIn);

//Convert a structure style vector to array style.
void ConvertVectorS2A(VECTORFS VectorStructIn, VECTORFA VectorArrayOut);

//Convert an array style 3ub color to structure style.
COLOR3UBS ConvertColor3ubA2S(COLOR3UBA ColorArrayIn);

//Convert a structure style 3ub color to array style.
void ConvertColor3ubS2A(COLOR3UBS ColorStructIn, COLOR3UBA ColorArrayOut);

//Convert an array style 4ub color to structure style.
COLOR4UBS ConvertColor4ubA2S(COLOR4UBA ColorArrayIn);

//Convert a structure style 4ub color to array style.
void ConvertColor4ubS2A(COLOR4UBS ColorStructIn, COLOR4UBA ColorArrayOut);