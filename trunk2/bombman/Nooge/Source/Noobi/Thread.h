#ifndef ThreadH
#define ThreadH
#include <windows.h>
#include <map>

using namespace std;

//Thread object. Just a simple thread for engine rendering test.
//****** THIS IS NOT YOUR GRANDMA'S CTHREAD *******
class CThread
{
	public:
		//Simple constructor.
		CThread(bool CreateSuspended);

		//Default destructor.
		virtual ~CThread();

		//Resume the thread.
		void Resume();

		//Pause the thread.
		void Suspend();

		//Terminate the thread.
		void Terminate();

	protected:
		//If the thread terminated.
		bool mTerminated;

	private:
		//Default constructor.
		CThread();

		//Static Execute function.
		static void StaticExecute();

		//Execute function.
		virtual void Execute() = 0;

	private:
		//Thread handle.
		HWND mhWnd;

		//Thread ID.
		unsigned mThreadID;
		
};


#endif