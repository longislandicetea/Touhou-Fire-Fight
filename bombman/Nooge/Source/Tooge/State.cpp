#include"State.h"
#include<algorithm>

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
	//int temp = rand();//rand move or drop bomb
	//if(temp%9 == 0)
	//return rand()%5;
	//return MOVE_UP;
	return IDLE;
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
	int row = safe.GetRow();//character's pos
	int col = safe.GetCol();
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

	if(safe.GetRow() == row+dirY[0] && safe.GetCol()== col+dirX[0]  )//can NPC pass the next 格子
		return MOVE_LEFT;
	else if(safe.GetRow() == row+dirY[1] && safe.GetCol()== col+dirX[1] )
		return MOVE_DOWN;
	else if(safe.GetRow() == row+dirY[2] && safe.GetCol() == col+dirX[2] )
		return MOVE_RIGHT;
	else if(safe.GetRow() == row+dirY[3] && safe.GetCol()== col+dirX[3] )
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

	//choose action
	float can= Grid::SideLen/mCtrl->GetCharacter()->GetSpeed();//若有危险 能否通过
	if(path.empty() || (!path.empty()&& mCtrl->GetDangerGrid()->GetValue(path.top().col,path.top().row)<=can))
		return IDLE;
	else if(myPosition.GetCol()<path.top().GetCol() )
		return MOVE_RIGHT;
	else if(myPosition.GetCol()>path.top().GetCol() )
		return MOVE_LEFT;
	else if(myPosition.GetRow()>path.top().GetRow() )
		return MOVE_UP;
	else if(myPosition.GetRow()<path.top().GetRow())
		return MOVE_DOWN;
	return IDLE;
}

//////////////////////////////OpenState////////////////////////////
OpenState::OpenState(NPCController* ctrl):
State(ctrl)
{}

int OpenState::GetAction()
{
	AIMap* interest = mCtrl->GetInterestGrid();
	Pos myPosition = Pos(mCtrl->GetCharacter()->GetBoundingBox().Row(),mCtrl->GetCharacter()->GetBoundingBox().Col());
	for(int t = 3;t>0;--t)
	{
		if(interest->GetValue(myPosition) ==t)
			return DROP_BOMB;
		std::vector<Pos> positions = interest->GetValuePositions(t);
		stack<Pos> minPath;
		for(int i = 0;i<positions.size();++i)
		{
			stack<Pos> path= mCtrl->getPathTo(positions[i]);
			
			if((!path.empty() && minPath.empty() ) || 
				(!path.empty() && !minPath.empty() && path.size()<minPath.size()))
			{
				minPath = path;
			}
		}
		if(!minPath.empty())
		{
			if(myPosition.GetCol()<minPath.top().GetCol() )
					return MOVE_RIGHT;
				else if(myPosition.GetCol()>minPath.top().GetCol() )
					return MOVE_LEFT;
				else if(myPosition.GetRow()>minPath.top().GetRow() )
					return MOVE_UP;
				else if(myPosition.GetRow()<minPath.top().GetRow())
					return MOVE_DOWN;
		}
	}
	return IDLE;
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

