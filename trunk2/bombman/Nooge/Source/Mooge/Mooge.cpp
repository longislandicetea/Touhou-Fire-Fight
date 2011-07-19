#include "Mooge.h"
#include "PrimitiveManager.h"
#include "CameraManager.h"
#include "TextManager.h"
#include "Core.h"
#include "Console.h"
#include "Auxiliary.h"
#include "Stage.h"
#include <gl/GL.h>
#include <gl/GLU.h>

//Default constructor.
CMooge::CMooge(): Core(NULL), Console(NULL), Primitives(NULL), Cameras(NULL), Text(NULL), CurrentStage(NULL)
{
	Core = new CCore();
	Primitives = new CPrimitiveManager();
	Cameras = new CCameraManager();
	Text = new CTextManager();
	Console = new CConsole(800, 600, 12, 0);
	Auiliary = new CAuxiliary();
}

//Default destructor.
CMooge::~CMooge()
{
	delete Auiliary;
	delete Console;
	delete Text;
	delete Cameras;
	delete Primitives;
	delete Core;
}

//Render.
void CMooge::Render()
{
	//Clear the window with current clearing color
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 800, 600, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//draw 2d
	if (!CurrentStage.IsNull())
	{
		CurrentStage->Draw(false);
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glDisable(GL_DITHER);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	//Post camera to current position.
	glMatrixMode(GL_MODELVIEW);
	Cameras->Post();

	//draw 3d
	if (!CurrentStage.IsNull()) 
	{
		CurrentStage->Draw(true);
	}

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 800, 600, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//draw 2d
	if (!CurrentStage.IsNull())
	{
		CurrentStage->Draw(false);
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();*/
	
	SwapBuffers(Core->mhDC);

	//Render finish.
	Sleep(0);
}

void CMooge::Update(float dt)
{
	if (!CurrentStage.IsNull()) 
	{
		CurrentStage->Update(dt);
	}
}
