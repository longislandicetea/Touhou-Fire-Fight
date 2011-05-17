#ifndef TextureH
#define TextureH

#include <string>
#include "Ref.h"

class Texture {
public:
	~Texture();

	static void Bind(Ref<Texture> tex);
	static Ref<Texture> Load(const std::string &filename);

	float GetWidth();
	float GetHeight();
	float GetID();

private:
	Texture(float width, float height, void *data);
	float mWidth, mHeight;
	unsigned int mId;
};

#endif