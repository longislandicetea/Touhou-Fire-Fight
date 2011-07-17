#pragma once

#include "Texture.h"
#include "Ref.h"
#include "GameObjectContainer.h"
#include <string>

class Image : public Sprite
{
public:
	Image(const std::string& filename,int width, int height);
	virtual void Draw(bool is3D);
	//void Draw(float x1,float y1,float x2,float y2);

private:
	Ref<Texture> mTexture;
	int mWidth, mHeight;
};