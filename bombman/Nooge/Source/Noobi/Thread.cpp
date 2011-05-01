#include "Thread.h"
#include <process.h>
#include "ThreadManager.h"

//Default constructor.
CThread::CThread()
{

}

//Simple constructor.
CThread::CThread(bool CreateSuspended): mTerminated(false), mThreadID(0)
{
	mhWnd = (HWND)_beginthreadex(
		0,
		0,
		(unsigned (_stdcall *)(void *)) StaticExecute,
		NULL,
		(CreateSuspended)?(CREATE_SUSPENDED):(NULL),
		(unsigned *) &mThreadID
		);

	if(mhWnd != NULL)
	{
		//Remember this object in map.
		CThreadManager::GetInstance()->AddThread(mThreadID, this);
	}
}

//Default destructor.
CThread::~CThread()
{
	CloseHandle(mhWnd);
	CThreadManager::GetInstance()->RemoveThread(mThreadID);
	mhWnd = NULL;
	mThreadID = 0;
	mTerminated = false;
}

//Resume the thread.
void CThread::Resume()
{
	ResumeThread(mhWnd);
}

//Pause the thread.
void CThread::Suspend()
{

}

//Force terminate the thread.
void CThread::Terminate()
{
	mTerminated = true;
}

void CThread::StaticExecute()
{
	//Try find the Thread ptr in manager first.
	unsigned tmpThreadID = GetCurrentThreadId();
	CThread* tmpThread = CThreadManager::GetInstance()->GetThread(tmpThreadID);

	//Found it. Execute the thread.
	if(tmpThread != NULL)
	{
		tmpThread->Execute();
	}
}
