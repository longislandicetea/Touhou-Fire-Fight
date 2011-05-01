#include "Auxiliary.h"
#include <stdio.h>
#include <windows.h>
#include <gl/GL.h>
#include "2DText.h"
#include "Line.h"
#include "MoogeType.h"

unsigned int CAuxiliary::BUILDINOBJECTSSEQ = 0;

//Default constructor.
CAuxiliary::CAuxiliary(): mCoordRange(500.0), mGridSize(10.0), mXAxis(NULL), mYAxis(NULL), mZAxis(NULL), mAxisVis(true),
	mGridLineVis(true), mFPSText(NULL), mFPSVis(true), mVersionText(NULL), mTitleText(NULL), mVersionInfoVis(true),
	mCurrentSample(0), mFPS(0.0), mOldTime(0), mNewTime(0)
{
	//Setup build-in Engine info display.
	BUILDINOBJECTSSEQ++;
	mTitleText = new C2DText("Mooge", 0, 12, BUILDINOBJECTSSEQ);
	BUILDINOBJECTSSEQ++;
	mVersionText = new C2DText("Version 0.0.0.1 alpha", 0, 24, BUILDINOBJECTSSEQ);
	
	//Setup build-in FPS display.
	BUILDINOBJECTSSEQ++;
	mFPSText = new C2DText("FPS: ", 0, 36, BUILDINOBJECTSSEQ);

	//Setup build-in grids line.
	for (float f = -mCoordRange ; f <= mCoordRange ; f+= mGridSize)
	{
		//Grid lines that parallel with x-axis.
		BUILDINOBJECTSSEQ++;
		VECTORFA XLineStartPos = { -mCoordRange, 0.0, f };
		VECTORFA XLineEndPos = { mCoordRange, 0.0, f };
		mGridLineVec.push_back(new CLine(XLineStartPos, XLineEndPos, BUILDINOBJECTSSEQ));

		//Grid lines that paralled with z-axis.
		BUILDINOBJECTSSEQ++;
		VECTORFA ZLineStartPos = { f, 0.0, -mCoordRange };
		VECTORFA ZLineEndPos = { f, 0.0, mCoordRange };
		mGridLineVec.push_back(new CLine(ZLineStartPos, ZLineEndPos, BUILDINOBJECTSSEQ));
	}

	//Setup build-in 3-axis.
	//XAxis.
	BUILDINOBJECTSSEQ++;
	VECTORFA XAxisStartPos = { -mCoordRange, 0.0, 0.0 };
	VECTORFA XAxisEndPos = { mCoordRange, 0.0, 0.0 };
	COLOR4UBS XAxisColor(255, 0, 0, 128);
	mXAxis = new CLine(XAxisStartPos, XAxisEndPos, BUILDINOBJECTSSEQ);
	mXAxis->SetColor(XAxisColor);

	//YAxis.
	BUILDINOBJECTSSEQ++;
	VECTORFA YAxisStartPos = { 0.0, -mCoordRange, 0.0 };
	VECTORFA YAxisEndPos = { 0.0, mCoordRange, 0.0 };
	COLOR4UBS YAxisColor(0, 255, 0, 128);
	mYAxis = new CLine(YAxisStartPos, YAxisEndPos, BUILDINOBJECTSSEQ);
	mYAxis->SetColor(YAxisColor);

	//ZAxis.
	BUILDINOBJECTSSEQ++;
	VECTORFA ZAxisStartPos = { 0.0, 0.0, -mCoordRange };
	VECTORFA ZAxisEndPos = { 0.0, 0.0, mCoordRange };
	COLOR4UBS ZAxisColor(0, 0, 255, 128);
	mZAxis = new CLine(ZAxisStartPos, ZAxisEndPos, BUILDINOBJECTSSEQ);
	mZAxis->SetColor(ZAxisColor);

	//Precalaulate oldtime/LastFPSRefreshTime.
	mOldTime = clock();
	mNewTime = 0;
	mLastFPSRefreshTime = clock();
	ZeroMemory(mFPSSamples, sizeof(float)*64);
}

//Default destructor.
CAuxiliary::~CAuxiliary()
{
	delete mZAxis;
	delete mYAxis;
	delete mXAxis;

	for(vector<CLine*>::iterator VecIter = mGridLineVec.begin() ; VecIter != mGridLineVec.end() ; VecIter++)
	{
		delete *VecIter;
	}
	mGridLineVec.clear();

	delete mFPSText;
	delete mVersionText;
	delete mTitleText;
}

void CAuxiliary::DrawVersionInfo(unsigned int FontList)
{
	mTitleText->Draw(FontList);
	mVersionText->Draw(FontList);
}

void CAuxiliary::DrawFPS(unsigned int FontList)
{
	//Calculate FPS and draw it.
	//CalcFPS();

	//Refresh FPS text every 1 second.
	if(clock() - mLastFPSRefreshTime > 1000)
	{
		//Translate float to string. Pass it to 2D text.
		char FpsStr[16];
		sprintf(FpsStr, "FPS: %f", mFPS);
		mFPSText->SetText(FpsStr);
		mLastFPSRefreshTime = clock();
	}

	mFPSText->Draw(FontList);
}

void CAuxiliary::DrawAxis()
{
	glLineWidth(3.0);
	glBegin(GL_LINES);
		mXAxis->Draw();
		mYAxis->Draw();
		mZAxis->Draw();
	glEnd();
}

void CAuxiliary::DrawXZGrids()
{
	glLineWidth(0.5);
	glBegin(GL_LINES);
		for(vector<CLine*>::iterator VecIter = mGridLineVec.begin() ; VecIter != mGridLineVec.end() ; VecIter++)
		{
			(*VecIter)->Draw();
		}
	glEnd();
}

//Calculat FPS.
void CAuxiliary::CalcFPS()
{
	//Get current time.
	mNewTime = clock();
	//Time difference.
	float dt = static_cast<float>(mNewTime - mOldTime);
	//Prevent divided by 0
	if(dt == 0.0)
		dt = 1.0;
	//Collect sample into array.
	mFPSSamples[mCurrentSample % 64] = (1.0f / dt)*CLOCKS_PER_SEC;

	//Calculate sample average.
	float fps = 0;
	for (int i = 0; i < 64; i++)
		fps += mFPSSamples[i];
	fps /= 64;

	//Resolute FPS.
	mFPS = fps;

	mCurrentSample++;
	if(mCurrentSample > 10000000000)
		mCurrentSample = 0;

	mOldTime = mNewTime;
}

//public interface.
void CAuxiliary::SetVersionInfoVis(bool Vis)
{
	mVersionInfoVis = Vis;
}

void CAuxiliary::SetFPSVis(bool Vis)
{
	mFPSVis = Vis;
}

void CAuxiliary::SetAxisVis(bool Vis)
{
	mAxisVis = Vis;
}

void CAuxiliary::SetXZGridVis(bool Vis)
{	
	mGridLineVis = Vis;
}
