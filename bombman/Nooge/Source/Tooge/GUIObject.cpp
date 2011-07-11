#include "GUIObject.h"

GUIObject::GUIObject( Ref<Image> image,float x1,float y1,float x2,float y2)
{
	mImage = image;
	mX1 = x1;
	mY1 = y1;
	mX2 = x2;
	mY2 = y2;
}

void GUIObject::Draw()
{
	mImage->Draw(mX1,mY1,mX2,mY2);
}
