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

protected:
	Ref<Texture> mTexture;
	int mWidth, mHeight;
	int mX,mY;
};