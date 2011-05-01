#ifndef ConsoleH
#define ConsoleH
#include <vector>

using namespace std;

class CMooge;
class C2DText;

class CConsole
{
	friend CMooge;
	public:
		//Active the console.
		void Activate();

		//Hide console.
		void Deactivate();

		//Is console activate?
		bool IsActivate();

		//User Input.
		void Input(char c);

	private:
		//Default constructor.
		CConsole(unsigned int ScreenWidth, unsigned int ScreenHeight, unsigned int FontHeight, unsigned FontWidth);

		//Default destructor.
		~CConsole();

		//Draw console texts.
		void Draw(unsigned int FontList);

	private:
		//Is console activate?
		bool mActivate;

		//Display text list.
		vector<C2DText*> mTextLineVec;

		//How many lines on the current screen?
		unsigned int mLineCount;
		//How many chars in a line?
		unsigned int mLineCharCount;

		//Remember least user input command.
		vector<string*> mCommandHistory;

		//Current input command.
		string mCurrentCommand;
		string mCommander;
};

#endif