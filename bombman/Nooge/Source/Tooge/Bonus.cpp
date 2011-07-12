#include "Bonus.h"
#include "App.h"
#include "GameStage.h"

void Bonus::CreateBonus(int x,int y)
{
	GameStage* gs = (GameStage*)(App::Inst().CurrentStage());
	Ref<GameObject> bonus = gs->CreateBonus();
	if(!bonus.IsNull())
	{
		bonus->SetPos(x,0,y);
		gs->AddBonus(bonus);
	}
}
