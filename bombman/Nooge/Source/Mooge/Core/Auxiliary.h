#ifndef AuxiliaryH
#define AuxiliaryH
#include <vector>
#include <time.h>

using namespace std;

class CMooge;
class CLine;
class C2DText;

//Axuiliary class contain the following build-in functions:
//Engine info display using C2DText object.
//FPS calculate/display using C2DText object.
//x-z plain grids display.
//3-axis display.

class CAuxiliary
{
	//Only CMooge class(main interface of engine) has the power to use me.
	friend CMooge;

	public:
		//public interface.
		void SetVersionInfoVis(bool Vis);
		void SetFPSVis(bool Vis);
		void SetAxisVis(bool Vis);
		void SetXZGridVis(bool Vis);

	private:
		//Default constructor.
		CAuxiliary();

		//Default destructor.
		~CAuxiliary();

		void DrawVersionInfo(unsigned int FontList);
		void DrawFPS(unsigned int FontList);
		void DrawAxis();
		void DrawXZGrids();
	
		//Calculat FPS.
		void CalcFPS();

	private:
		//Engine info.
		bool mVersionInfoVis;
		C2DText* mTitleText;
		C2DText* mVersionText;

		//FPS display.
		bool mFPSVis;
		C2DText* mFPSText;

		//Grid line map.
		bool mGridLineVis;
		vector<CLine*> mGridLineVec;

		//3-Axis lines.
		bool mAxisVis;
		CLine* mXAxis;
		CLine* mYAxis;
		CLine* mZAxis;

		//Axis and grids extand range.
		float mCoordRange;
		//Grid size.
		float mGridSize;

		//==== FPS calculate ====
		//FPS sample array.
		float mFPSSamples[64];
		int mCurrentSample;
		float mFPS;
		clock_t mOldTime;
		clock_t mNewTime;
		clock_t mLastFPSRefreshTime;
		//=======================

		//Build in object ID generator.
		static unsigned int BUILDINOBJECTSSEQ;
};

#endif
