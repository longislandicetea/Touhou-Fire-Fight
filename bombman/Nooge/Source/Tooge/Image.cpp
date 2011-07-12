#include "Image.h"

#include <windows.h>
#include <gl\GL.h>


Image::Image(const std::string& filename)
{
	mTexture = Texture::Load(filename);
}

void Image::Draw(float x1,float y1,float x2,float y2)
{
	Texture::Bind(mTexture);
	
	//glPushMatrix();
	glMatrixMode( GL_PROJECTION );

	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,800,600, 0, -1, 1);

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();
	glBegin( GL_QUADS );
	glTexCoord2f(0.0,0.0);glVertex3f(x1,y1,0.0);
	glTexCoord2f(0.0,1.0);glVertex3f(x1,y2,0.0);
	glTexCoord2f(1.0,1.0);glVertex3f(x2,y2,0.0);
	glTexCoord2f(1.0,0.0);glVertex3f(x2,y1,0.0);
	glEnd();
	glPopMatrix();

	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
