#include"State.h"

/////////////////////////////typedf//////////////
typedef struct
{
	float x;
	float y;
	float z;
}Vector3;
///////////////////////////////State/////////////////////////////////

State::State(FSM* fsm,int TNum)
{
	mTNum = TNum;
	for(int i = 0;i<TNum;++i)
	{
		mTransitionList.push_back(NULL);
	}
	mOwner = fsm;
}

Ref<State> State::Update(float dt)
{
    for (int i = 0; i < mTNum; ++i)
        if (mTransitionList[i]->IsTrue())
            return mTransitionList[i] ->GetNextState();
    return Ref<State>(this);
}

int State::GetAction()
{
	return 0;//??
}




///////////////////////////////ClearPathState///////////////////////
/*int ClearPathState::GetAction()
{
	//NPCController* controller = mOwner->GetNPCController();
    // get the best interesting position
    int x = 0, y = 0;
    AIMap* interest = controller->GetInterestGrid();
    interest->GetBestValuePosition(x,y);
    // compute the path
   // List<Vector3>* path = controller->getPathTo(x,y);
   // Vector3 myPosition = brain->getBomberman()->getPosition();  
    // move to the first point
   /* if (myPosition.x < path[0].x)
        return CharacterController::MOVE_RIGHT;
    else if (myPosition.x > path[0].x)
        return CharacterController::MOVE_LEFT;
    else if (myPosition.y < path[0].y)
        return CharacterController::MOVE_UP;
    else if (myPosition.y > path[0].y)
        return CharacterController::MOVE_DOWN;
    return CharacterController::IDLE;*/
//}

