#include"State.h"

/////////////////////////////typedf//////////////
typedef struct
{
	float x;
	float y;
	float z;
}Vector3;

///////////////////////////////State/////////////////////////////////



State* State::Update(float dt)
{
	vector<Transition*>::iterator it = mTransitionList.begin();
	vector<Transition*>::iterator end = mTransitionList.end();
    for (; it !=end ; ++it)
        if ((*it)->IsTrue())
            return (*it) ->GetNextState();
    return this;
}



void State::AddTransition(Transition* transition)
{
	mTransitionList.push_back(transition);
}

State::State(NPCController* ctrl)
{
	mCtrl = ctrl;
}

////////////////////////////////SillyState////////////////////////////////
SillyState::SillyState(NPCController* ctrl):
State(ctrl)
{}

int SillyState::GetAction()
{
	return IDLE;
	//return DROP_BOMB;
}

////////////////////////////////FleeState///////////////////////////////

FleeState::FleeState(NPCController* ctrl):
State(ctrl)
{
}

int FleeState::GetAction()
{
    static int dirX[4] = { -1, 0, 1,  0};
	static int dirY[4] = {  0, 1, 0, -1};
	Pos safe;

 	Grid g = mCtrl->GetCharacter()->GetBoundingBox();
	safe.row = g.Row();
	safe.col = g.Col();
	int row = safe.row;//character's pos
	int col = safe.col;
	AIMap* dangerGrid = mCtrl->GetDangerGrid();

	//find safer place
	for(int i = 0;i<4;++i)
	{
		float safeValue = dangerGrid->GetValue(col+dirX[i],row+dirY[i]);
		if(safeValue!=-DWALL && safeValue!=-UWALL && safeValue >= dangerGrid->GetValue(safe.col,safe.row))
		{
			safe.row = row+dirY[i];
			safe.col = col+dirX[i];
		}
	}

	//choose action
	if(safe.row == row+dirY[0] && safe.col == col+dirX[0])
		return MOVE_LEFT;
	else if(safe.row == row+dirY[1] && safe.col == col+dirX[1])
		return MOVE_DOWN;
	else if(safe.row == row+dirY[2] && safe.col == col+dirX[2])
		return MOVE_RIGHT;
	else if(safe.row == row+dirY[3] && safe.col == col+dirX[3])
		return MOVE_UP;
	else
		return IDLE;

}

///////////////////////////////SearchBonusState////////////////////
SearchBonusState::SearchBonusState(NPCController* ctrl):
State(ctrl)
{}

int SearchBonusState::GetAction()
{
	Pos myPosition = Pos(mCtrl->GetCharacter()->GetBoundingBox().Col(),mCtrl->GetCharacter()->GetBoundingBox().Row());
	Pos nearestBonus = mCtrl->NearestBonusPos();
	std::stack<Pos> path = mCtrl->getPathTo(nearestBonus);
	if(path.empty())
		return IDLE;
   else if(myPosition.col<path.top().col)
		return MOVE_RIGHT;
	else if(myPosition.col>path.top().col)
		return MOVE_LEFT;
	else if(myPosition.row>path.top().row)
		return MOVE_UP;
	else if(myPosition.row<path.top().row)
		return MOVE_DOWN;
	
}

///////////////////////////////ClearPathState///////////////////////
int ClearPathState::GetAction()
{
	
    // get the best interesting position
    int x = 0, y = 0;
	AIMap* interest =mCtrl->GetInterestGrid();
return 0;}
//	interest->GetBestValuePosition(x,y);
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

