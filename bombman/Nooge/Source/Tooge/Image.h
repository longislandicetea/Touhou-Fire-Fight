#pragma once

#include "Texture.h"
#include "Ref.h"
//#include "GameObject.h"
#include <string>

class Image
{
public:
	Image(const std::string& filename);
	void Draw(float x1,float y1,float x2,float y2);

private:
	Ref<Texture> mTexture;
};