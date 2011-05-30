#include "Dwall.h"
#include <iostream>
using namespace std;

Dwall::Dwall()
{
	mModel = Md2Object::Load("c:\\dwall.md2","c:\\dwallt.bmp");
	this->AddChild(mModel);
}

Dwall::~Dwall()
{
	cout << "Dwall: " << endl;
}
