#include "Font.h"

#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <gl/gl.h>

Font::Font()
{
	screenX = 0;
	screenY = 0;
	xpos = 0.0;
	ypos = 0.0;
	zpos = 0.0;
}

Font::Font(char *name, int size)
{
	screenX = 0;
	screenY = 0;
	xpos = 0.0;
	ypos = 0.0;
	zpos = 0.0;
	Build(name, size);
}

Font::~Font()
{
	glDeleteLists(callList, 96);
}

void Font::Build(char *name, int size)
{
	HFONT hFont;	// font ID
	HDC hDC;		// device context

	hDC = wglGetCurrentDC();
	callList = glGenLists(96);

	if (stricmp(name, "symbol") == 0)
	{
		hFont = CreateFont(-size, 0,0,0,FW_BOLD, FALSE, FALSE, FALSE, SYMBOL_CHARSET,
			OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
			FF_DONTCARE | DEFAULT_PITCH, name);
	}
	else
	{
		hFont = CreateFont(-size, 0,0,0,FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET,
			OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, 
			FF_DONTCARE | DEFAULT_PITCH, name);
	}

	SelectObject(hDC, hFont);
	wglUseFontBitmaps(hDC, 32, 96, callList);
}

void Font::Print(const char *str, ...)
{
	char text[256];
	va_list args;

	if (str == NULL)
		return;

	va_start(args, str);
	vsprintf(text, str, args);
	va_end(args);

	glPushMatrix();
	glColor4f(r, g, b, a);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	//glTranslatef(0.0f, 0.0f, -1.0f);
	
	glPushMatrix();
	glLoadIdentity();

	glOrtho(0,800,600, 0, -1, 1);
	if (xpos == 0.0 && ypos == 0.0 && zpos == 0.0)
		glRasterPos2i(screenX, screenY);
	else
		glRasterPos3f(xpos, ypos, zpos);

	//glPushAttrib(GL_LIST_BIT);
	glListBase(callList - 32);
	glCallLists(strlen(str), GL_UNSIGNED_BYTE, str);
	//glPopAttrib();
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Font::ClearFont()
{
	glDeleteLists(callList, 96);
}