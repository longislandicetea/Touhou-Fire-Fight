#include "GUIObject.h"

GUIObject::GUIObject( Ref<Image> image )
{
	mImage = image;
}

void GUIObject::Draw()
{
	mImage->Draw(mX1,mY1,mX2,mY2);
}
