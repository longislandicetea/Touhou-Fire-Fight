#include "Image.h"

#include <windows.h>
#include <gl\GL.h>


Image::Image(const std::string& filename)
{
	mTexture = Texture::Load(filename);
}

void Image::Draw(float x1,float y1,float x2,float y2)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	Texture::Bind(mTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);glVertex3f(x1,0.0,y1);
	glTexCoord2f(0.0,1.0);glVertex3f(x1,0.0,y2);
	glTexCoord2f(1.0,1.0);glVertex3f(x2,0.0,y2);
	glTexCoord2f(1.0,0.0);glVertex3f(x2,0.0,y1);
	glEnd();
	glFlush();
}
