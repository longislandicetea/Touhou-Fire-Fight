#include "Dwall.h"
#include <iostream>
using namespace std;

Dwall::Dwall()
{
	mModel = Md2Object::Load("c:\\wall.md2","c:\\wall1.bmp");
	this->AddChild(mModel);
}

Dwall::~Dwall()
{
	cout << "Dwall: " << this << endl;
}
