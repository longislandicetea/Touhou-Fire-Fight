#include"State.h"

/////////////////////////////typedf//////////////
typedef struct
{
	float x;
	float y;
	float z;
}Vector3;
///////////////////////////////State/////////////////////////////////



Ref<State> State::Update(float dt)
{
	vector<Ref<Transition>>::iterator it = mTransitionList.begin();
	vector<Ref<Transition>>::iterator end = mTransitionList.end();
    for (; it !=end ; ++it)
        if ((*it)->IsTrue())
            return (*it) ->GetNextState();
    return Ref<State>(this);
}

int State::GetAction()
{
	return 0;//??
}

void State::AddTransition(Ref<Transition> transition)
{
	mTransitionList.push_back(transition);
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

