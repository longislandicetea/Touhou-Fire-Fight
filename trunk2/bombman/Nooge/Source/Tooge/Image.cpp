#include "Image.h"

#include <windows.h>
#include <gl\GL.h>


Image::Image(const std::string& filename,int width,int height)
{
	mTexture = Texture::Load(filename);
	mWidth = width;
	mHeight = height;
}

void Image::Draw(bool is3D)
{
	if(is3D) return;
	
	Texture::Bind(mTexture);
	int x = this->GetX();
	int y = this->GetY();

	glBegin( GL_QUADS );
	glTexCoord2f(0.0,0.0);glVertex3f(0.0,0.0,0.0);
	glTexCoord2f(0.0,1.0);glVertex3f(0.0,mHeight,0.0);
	glTexCoord2f(1.0,1.0);glVertex3f(mWidth,mHeight,0.0);
	glTexCoord2f(1.0,0.0);glVertex3f(mWidth,0.0,0.0);
	glEnd();
}