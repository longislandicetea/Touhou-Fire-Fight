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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw all primitive objects.
	Primitives->Draw();

	//Draw auxiliary objects here.
	//These thing could be removed in release version.
	if(Auiliary->mGridLineVis)
		Auiliary->DrawXZGrids();
	if(Auiliary->mAxisVis)
		Auiliary->DrawAxis();

	//Post camera to current position.
	glMatrixMode(GL_MODELVIEW);
	Cameras->Post();

	//Check if current console is activate.
	if(Console->mActivate)
	{
		//Draw console text.
		Console->Draw(Core->GetFontList());
	}else
	{
		//Draw 2DText.
		Text->Draw(Core->GetFontList());
		if(Auiliary->mVersionInfoVis)
			Auiliary->DrawVersionInfo(Core->GetFontList());
		if(Auiliary->mFPSVis)
			Auiliary->DrawFPS(Core->GetFontList());
	}

	/*glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(10.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glVertex3f(10.0, 10.0, 10.0);


	glEnd();*/

	if (!CurrentStage.IsNull()) {
		CurrentStage->Draw();
	}

	SwapBuffers(Core->mhDC);

	//Render finish.

	//Calculate FPS.
	Auiliary->CalcFPS();
	Sleep(0);
}

void CMooge::Update(float dt)
{
	if (!CurrentStage.IsNull()) 
	{
		CurrentStage->Update(dt);
	}
}
