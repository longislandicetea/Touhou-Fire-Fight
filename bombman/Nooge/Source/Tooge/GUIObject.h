#pragma once

#include "GameObjectContainer.h"
#include "Image.h"

class GUIObject : public Sprite
{
public:
	GUIObject(Ref<Image> image);
	void Draw();
private:
	Ref<Image> mImage;
	float mX1,mY1,mX2,mY2;
};