#ifndef ThreadManagerH
#define ThreadManagerH
#include <map>

using namespace std;

class CThread;

class CThreadManager
{
	public:
		//Get the singlton instance.
		static CThreadManager* GetInstance();

		//Self destroy the singlton instance.
		bool DeleteInstance();

		//---------------------------------- [CThread Manage Method] ------------------------------------
		//Add a CThread ptr to CThreadManager.
		bool AddThread(unsigned ThreadID, CThread* Thread);

		//Remove a CThread ptr from mTreadMap.
		bool RemoveThread(unsigned ThreadID);

		//Check if the thread map is empty.
		bool IsThreadMapEmpty();

		//Search the mTreadMap for hWnd key value, if exist, return the associated CThread ptr.
		CThread* GetThread(unsigned ThreadID);
		//------------------------------------------------------------------------------------------------

	private:
		//cant be new.
		CThreadManager();

		//Cant be destroy.
		//Only self destroy is allow. See DeleteInstance();
		~CThreadManager();
	
	private:
		//Singoeton instance here.
		static CThreadManager* mInstance;

		//Manage all exist thread in this map.
		static map<unsigned, CThread*> mTreadMap;

};

#endif