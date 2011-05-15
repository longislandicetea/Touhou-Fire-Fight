#ifndef TextureH
#define TextureH
#include "Ref.h"

class Texture {
public:
	Texture(float width, float height, void *data);
	~Texture();

	static void Bind(Ref<Texture> tex);
	static Ref<Texture> LoadBMP(char *filename);

	float GetWidth();
	float GetHeight();
	float GetID();

private:
	float mWidth, mHeight;
	unsigned int mId;
};

#endif