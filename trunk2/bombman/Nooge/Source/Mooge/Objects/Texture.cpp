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
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	

	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, 
		GL_RGBA, GL_UNSIGNED_BYTE, data);
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

Ref<Texture> Texture::Load( const std::string &filename )
{
	AUX_RGBImageRec *img = auxDIBImageLoadA(filename.c_str());
	int w = img->sizeX;
	int h = img->sizeY;

	unsigned char* buf = (unsigned char*)malloc(w*h*4*sizeof(unsigned char));


	for(int i = 0;i<w;++i)
	{
		for(int j = 0;j<h;++j)
		{
			int index = i*h+j;
			memcpy(&buf[index*4],&img->data[index*3],sizeof(unsigned char)*3);
			if(buf[index*4+0] == 0 && buf[index*4+1] == 0 && buf[index*4+2] == 0)
				buf[index*4+3] = 0;
			else
				buf[index*4+3] = 255;
		}
	}
	//mImg = auxDIBImageLoadA(filename.c_str());
	Ref<Texture> ret(new Texture(img->sizeX, img->sizeY, buf));
	free(img->data);
	free(img);
	free(buf);
	return ret;
}

/*void Texture::Display(float x,float y)
{
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,mWidth,0,mHeight,-1,1);							// Set Up An Ortho Screen

	glRasterPos2d(x,y);
	//glDrawPixels(img->sizeX,textureImage->sizeY,GL_RGB,GL_UNSIGNED_BYTE,textureImage->data);
	glPopMatrix();		
}*/
