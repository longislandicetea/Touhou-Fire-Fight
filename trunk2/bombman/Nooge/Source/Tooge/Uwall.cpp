#include "Uwall.h"
#include "Md2Object.h"
#include <iostream>
using namespace std;

Uwall::Uwall()
{
	mModel = Md2Object::Load("c:\\uwall.md2","c:\\uwall1.bmp");
	this->AddChild(mModel);
}

Uwall::~Uwall()
{
	cout << "uwall released " << this << endl;
}
