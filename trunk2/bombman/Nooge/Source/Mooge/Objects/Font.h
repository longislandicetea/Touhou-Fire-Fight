#pragma once

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "GameObjectContainer.h"
#include <vector>

class Font : public Sprite
{
public:
	Font();
	Font(char *name, int size,const std::string& str);
	~Font();

	void Build(char *name, int size);
	void ClearFont();

	virtual void Draw(bool is3D);

	void SetPos2D(int x, int y) { screenX = x; screenY = y; }
	void SetPos3D(float x, float y, float z) { xpos = x; ypos = y; zpos = z; }

	void SetRGB(float red, float green, float blue) { r = red; g = green; b = blue; a = 1.0; }
	void SetRGBA(float red, float green, float blue, float alpha) { r = red; g = green; b = blue; a = alpha; }

private:
	unsigned int texID;		// font texture id
	unsigned int callList;	// font display list
	float r, g, b, a;		// RGBA
	int screenX, screenY;	// screen coordinates
	float xpos, ypos, zpos;	// 3d coordinates
	std:: string content;

	void LoadTexture();		// loads the TGA font texture
	void CreateCallLists();	// creates the font display list
};