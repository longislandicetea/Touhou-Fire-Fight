#include "Texture.h"

#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLAux.h>

#pragma warning(disable: 4244)
Texture::Texture( float width, float height, void *data )
{
	mHeight = height;
	mWidth = width;
	glGenTextures(1,&mId);
	glBindTexture(GL_TEXTURE_2D, mId);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
}

Texture::~Texture()
{
	::glDeleteTextures(1, &mId);
}

void Texture::Bind( Ref<Texture> tex )
{
	if (!tex.IsNull())
	{
		glBindTexture(GL_TEXTURE_2D, tex->GetID());
	}
	else glBindTexture(GL_TEXTURE_2D, 0);
}

float Texture::GetWidth()
{
	return mWidth;
}

float Texture::GetHeight()
{
	return mHeight;
}

float Texture::GetID()
{
	return mId;
}

Ref<Texture> Texture::LoadBMP( char *filename )
{
	AUX_RGBImageRec *img = auxDIBImageLoadA(filename);
	Ref<Texture> ret(new Texture(img->sizeX, img->sizeY, img->data));
	free(img->data);
	free(img);
	return ret;
}