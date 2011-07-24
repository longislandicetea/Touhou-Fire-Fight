#include"Transition.h"
#include "WinFrame.h"


///////////////////////////////////////////////////////transition///////////////////////////////////////////////////
Transition::Transition(NPCController* ctrl, State* nextState):
mNextState(nextState)
{
	mCtrl = ctrl;
}

State* Transition::GetNextState()
{
	return mNextState;
}

//////////////////////////////////////////////////ToSilly/////////////////////////////////////////////
ToSilly::ToSilly(NPCController* ctrl,State* next):
Transition(ctrl,next)
{}

bool ToSilly::IsTrue()
{
	

	//if(mCtrl->GetCharacter()->GetBombCnt()==0)
	//LogTrace("Silly\n");
	return true;
	//}
	//return false;
}
//////////////////////////////////////////////////ToFlee///////////////////////////////////////////////

ToFlee::ToFlee(NPCController* ctrl,State* next):
Transition(ctrl,next)
{}

bool ToFlee::IsTrue()
{

	int row = mCtrl->GetCharacter()->GetBoundingBox().Row();
	int col = mCtrl->GetCharacter()->GetBoundingBox().Col();
	float speed = mCtrl->GetCharacter()->GetSpeed();
	if(mCtrl->GetDangerGrid()->GetValue(col,row)<=3.0)//Grid::SideLen/2/speed
	{
		LogTrace("Flee\n");
		return true;
	}

	return false;
}

////////////////////////////////////////////////ToSearchBonus////////////////////////////////////

ToSearchBonus::ToSearchBonus(NPCController* ctrl,State* next):
Transition(ctrl,next)
{}

bool ToSearchBonus::IsTrue()
{
	Pos NearestBonus = mCtrl->NearestBonusPos();
	if(NearestBonus == Pos(-1,-1) )//|| rand()%10<5
		return false;
	if(mCtrl->getPathTo(NearestBonus).size() >7)//如果太远就不去
		return false;
	LogTrace("SearchBonus\n");
	return true;
}

///////////////////////////////////////ToOpen///////////////////////////
ToOpen::ToOpen(NPCController* ctrl,State*next):
Transition(ctrl,next)
{}

bool ToOpen::IsTrue()
{
	for(int i = 4;i<=7;++i)
	{
		if(!mCtrl->GetInterestGrid()->GetValuePositions(i).empty())
		{
			LogTrace("Open\n");
			return true;
		}
	}
	return false;
}

////////////////////////////////////ToDropBomb////////////////////////////
ToDropBomb::ToDropBomb(NPCController* ctrl, State* next):
Transition(ctrl,next)
{}

bool ToDropBomb::IsTrue()
{
	if(true )
	{
		Pos myPosition = Pos(mCtrl->GetCharacter()->GetBoundingBox().Col(),mCtrl->GetCharacter()->GetBoundingBox().Row());
		float value = mCtrl->GetInterestGrid()->GetValue(myPosition);
		if(value>0 && value <=3
			&& value>=mCtrl->GetInterestGrid()->GetValue(myPosition.col+1,myPosition.row)
			&& value>=mCtrl->GetInterestGrid()->GetValue(myPosition.col-1,myPosition.row)
			&& value>=mCtrl->GetInterestGrid()->GetValue(myPosition.col,myPosition.row+1)
			&& value>=mCtrl->GetInterestGrid()->GetValue(myPosition.col,myPosition.row-1))
		{
			return true;
			LogTrace("DropBomb\n");
		}
	}
	return false;
}

//////////////////////////////////ToClearPath//////////////////////////////
ToClearPath::ToClearPath(NPCController* ctrl,State* next):
Transition(ctrl,next)
{}

bool ToClearPath::IsTrue()
{
	if(mCtrl->MostInterestPos() != Pos(-1,-1))
	{
		LogTrace("ClearPath\n");
		return true;
	}
	return false;
}

//////////////////////////////////////////////////ToTrigger////////////////////////////////
ToTrigger::ToTrigger(NPCController* ctrl, State* next):
Transition(ctrl,next)
{}

bool ToTrigger::IsTrue()
{
	if(mCtrl->IsTrigChance() 
		|| (mCtrl->GetCharacter()->HasTrigBonus() && mCtrl->GetCharacter()->TrigBonusTimer()->End() > 5.0))
		return true;
	return false;
}