#pragma once

#include "GameObjectContainer.h"
#include "Image.h"

class GUIObject : public Sprite
{
public:
	GUIObject(Ref<Image> image,float x1,float y1,float x2,float y2);
	void Draw(bool is3D);
private:
	Ref<Image> mImage;
	float mX1,mY1,mX2,mY2;
};