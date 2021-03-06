#include "GameStage.h"

#include <iostream>
#include <cstdlib>
#include <string.h>
#include "PlayerController.h"

#include "BBombPlus.h"
#include "BDrop.h"
#include "BFaster.h"
#include "BFlamePlus.h"
#include "BPush.h"
#include "BSlower.h"
#include "BTrigger.h"
#include "Grid.h"
#include "Decoration.h"
#include "Explosion.h"

#include "WinFrame.h"
#include "GUIObject.h"


#include "DataManager.h"
#include"gl/GL.h"
#include "App.h"

#include <vector>
#include <string.h>

Ref<GameObject> GameStage::CurrentMap()
{
        return mCurrentMap;
}

GameStage::GameStage( Ref<GameObject> map,int level) 
{
        //read map
        mCurrentMap = map;
        mBonusProb = cast<Map>(mCurrentMap)->GetBonusProb();

		//set bonus cnt
		memset(mBonusCnt,0,sizeof(mBonusCnt));

		//set countdown timer
		mCountdownTimer = 180;

		//set level
		mLevel = level;

        std::map< std::string,Ref<GameObject> > info = cast<Map>(mCurrentMap)->Parse();
        mDwall = info["dwall"];
        mUwall = info["uwall"];
        mNpc = info["npc"];
        mPlayer = info["player"];
        mBomb  = Ref<GameObject>(new Sprite);
        mBonus = Ref<GameObject>(new Sprite);
        mHUD = Ref<GameObject> (new Sprite);
		mExplosion = Ref<GameObject> (new Sprite);
		mDecoration = Ref<GameObject> (new Sprite);
		mBonusCntFont = Ref<GameObject>(new Sprite);

        //set gamestage
		this->AddChild(mHUD);
        this->AddChild(mDwall);
        this->AddChild(mUwall);
        this->AddChild(mNpc);
        this->AddChild(mPlayer);
        this->AddChild(mBomb);
        this->AddChild(mBonus);
		this->AddChild(mExplosion);
		this->AddChild(mDecoration);
		this->AddChild(mBonusCntFont);

		memset(isDead,0,sizeof(isDead));

        //background
		Ref<GameObject> bg;
		switch (mLevel)
		{
		case 1:
			bg = Ref<GameObject>(new Image(DataManager::GetDataPath("Image","bg1","resource\\data.ini"),800,600));
			if(! App::Inst().AudioSys()->IsBgmMute()) App::Inst().AudioSys()->PlayStream(0,"bgm3");
			break;
		case 2:
			bg = Ref<GameObject>(new Image(DataManager::GetDataPath("Image","bg2","resource\\data.ini"),800,600)); 
			if(! App::Inst().AudioSys()->IsBgmMute()) App::Inst().AudioSys()->PlayStream(0,"bgm2");
			break;
		case 3:
			bg = Ref<GameObject>(new Image(DataManager::GetDataPath("Image","bg3","resource\\data.ini"),800,600));
			if(! App::Inst().AudioSys()->IsBgmMute()) App::Inst().AudioSys()->PlayStream(0,"bgm1");
			break;
		}
		cast<Sprite>(mHUD)->AddChild(bg);

		//bamboo
		int r[2] = {1,-1};
		/*for(int i = 0;i<150;i += 4)
		{
			Ref<GameObject> bamboo = Decoration::CreateDecoration("bamboo");
			bamboo->SetPos(i,-5,-0.5);
			bamboo->SetRotateZ((rand()%20)*r[rand()%2]);
			cast<Sprite>(mDecoration)->AddChild(bamboo);
		}
		for(int i = 0;i<130;i += 4)
		{
			Ref<GameObject> bamboo = Decoration::CreateDecoration("bamboo");
			bamboo->SetPos(-0.5,-5,i);
			bamboo->SetRotateX((rand()%20)*r[rand()%2]);
			cast<Sprite>(mDecoration)->AddChild(bamboo);
		}
		for(int i = 0;i<130;i += 4)
		{
			Ref<GameObject> bamboo = Decoration::CreateDecoration("bamboo");
			bamboo->SetPos(150.5,-5,i);
			bamboo->SetRotateX((rand()%20)*r[rand()%2]);
			cast<Sprite>(mDecoration)->AddChild(bamboo);
		}*/
		
		//hud
		Ref<GameObject> imgBonus(new Image(DataManager::GetDataPath("Image","hudBonus","resource\\data.ini"),698,133));
		imgBonus->SetPos(51,0,0);
		cast<Sprite>(mHUD)->AddChild(imgBonus);
        
		//player state
		Ref<GameObject> npc1(new Image(DataManager::GetDataPath("Image","npc10","resource\\data.ini"),99,60));
		npc1->SetPos(13,144,0);
		cast<Sprite>(mHUD)->AddChild(npc1);

		//npc1 state
		Ref<GameObject> npc2(new Image(DataManager::GetDataPath("Image","npc20","resource\\data.ini"),107,60));
		npc2->SetPos(1,220,0);
		cast<Sprite>(mHUD)->AddChild(npc2);

		//npc2 state
		Ref<GameObject> npc3(new Image(DataManager::GetDataPath("Image","npc30","resource\\data.ini"),107,61));
		npc3->SetPos(694,140,0);
		cast<Sprite>(mHUD)->AddChild(npc3);

		//npc3 state
		Ref<GameObject> npc4(new Image(DataManager::GetDataPath("Image","npc40","resource\\data.ini"),107,61));
		npc4->SetPos(694,222,0);
		cast<Sprite>(mHUD)->AddChild(npc4);

		//timer
		mCountdownTimerFont = Ref<GameObject>(new Font("Comic Sans MS",18,"3:00"));
		cast<Font>(mCountdownTimerFont)->SetPos2D(226,35);
		cast<Sprite>(mHUD)->AddChild(mCountdownTimerFont);
		
		//bombplus-0
		Ref<GameObject> bombplus (new Font("Comic Sans MS",10,"0"));
		cast<Font>(bombplus)->SetPos2D(416,70);
		cast<Sprite>(mBonusCntFont)->AddChild(bombplus);

		//flameplus-1
		Ref<GameObject> flameplus (new Font("Comic Sans MS",10,"0"));
		cast<Font>(flameplus)->SetPos2D(537,70);
		cast<Sprite>(mBonusCntFont)->AddChild(flameplus);

		//faster--2
		Ref<GameObject> faster (new Font("Comic Sans MS",10,"0"));
		cast<Font>(faster)->SetPos2D(508,40);
		cast<Sprite>(mBonusCntFont)->AddChild(faster);

		//trigger--3
		Ref<GameObject> trigger (new Font("Comic Sans MS",10,"0"));
		cast<Font>(trigger)->SetPos2D(570,40);
		cast<Sprite>(mBonusCntFont)->AddChild(trigger);

		//push--4
		Ref<GameObject> pushbomb (new Font("Comic Sans MS",10,"0"));
		cast<Font>(pushbomb)->SetPos2D(475,70);
		cast<Sprite>(mBonusCntFont)->AddChild(pushbomb);

		//slower--5
		Ref<GameObject> slower (new Font("Comic Sans MS",10,"0"));
		cast<Font>(slower)->SetPos2D(384,40);
		cast<Sprite>(mBonusCntFont)->AddChild(slower);

		//drop--6
		Ref<GameObject> dropall (new Font("Comic Sans MS",10,"0"));
		cast<Font>(dropall)->SetPos2D(447,40);
		cast<Sprite>(mBonusCntFont)->AddChild(dropall);
}

GameStage::~GameStage()
{
        std::cout<<"gamestage released"<<std::endl;
}

Ref<GameObject> GameStage::Player()
{
        return cast<Sprite>(mPlayer)->GetChild(0);
}

bool GameStage::CanPass( GameObject* obj )
{
        //Sprite* dwallContainer = cast<Sprite>(mDwall);
        //Sprite* uwallContainer = cast<Sprite>(mUwall);
	/*Grid box = obj->GetBoundingBox();
	int row = box.Row();
	int col = box.Col();

	int dx[9] = {-1,-1,-1,0,0,0,1,1,1};
	int dy[9] = {-1,0,1,-1,0,1,-1,0,1};

	std::vector< Ref<Grid> > surroundWall;
	surroundWall.clear();

	for(int i = 0;i<9;++i)
	{
		int nRow = row + dx[i];
		int nCol = col + dy[i];

		if(nRow>=0 && nRow<13 && nCol>=0 && nCol<15)
		{
			if(mWallMap[nRow][nCol])
			{
				surroundWall.push_back(Ref<Grid>(new Grid(nRow,nCol)));
			}
		}
	}

	for(int j = 0;j<surroundWall.size();++j)
	{
		if(box.Intersect(*surroundWall[j]))
			return false;
	}
	return true;*/
	Grid box = obj->GetBoundingBox();
	int cnt = cast<Sprite>(mUwall)->NumOfChild();
	for(int j = 0;j<cnt;++j)
	{
		Ref<GameObject> child = cast<Sprite>(mUwall)->GetChild(j);
		Grid bBox = child->GetBoundingBox();
		if(bBox.Intersect(box))
		{
			return false;
		}
	}
	cnt = cast<Sprite>(mDwall)->NumOfChild();
	for(int i = 0;i<cnt;++i)
	{
		Ref<GameObject> child = cast<Sprite>(mDwall)->GetChild(i);
		if(!child.IsNull()){
		Grid bBox = child->GetBoundingBox();
		if(bBox.Intersect(box))
		{
			return false;
		}
		}
	}
	return true;
}

void GameStage::AddBomb( Ref<GameObject> bomb )
{
        cast<Sprite>(mBomb)->AddChild(bomb);
}

Ref<GameObject> GameStage::CreateBonus()
{
        int r = rand()%100+1;
        //int t = mBonusProb["AddBombP"];
        if(r < mBonusProb["AddBombP"])
        {
                return Ref<GameObject> (new BBombPlus);
        }
        /*if (r>30 && r<70)
                return Ref<GameObject> (new BBombPlus);*/
        //t += mBonusProb["AddFlameP"];
        else if (r< mBonusProb["AddBombP"]+mBonusProb["AddFlameP"])
        {
                return Ref<GameObject> (new BFlamePlus);
        }
        //t += mBonusProb["FasterP"];
        else if (r<mBonusProb["AddBombP"]+mBonusProb["AddFlameP"]+mBonusProb["FasterP"])
        {
                return Ref<GameObject> (new BFaster);
        }
        //t += mBonusProb["PushP"];
        else if (r<mBonusProb["AddBombP"]+mBonusProb["AddFlameP"]+mBonusProb["FasterP"]+mBonusProb["PushP"])
        {
                return Ref<GameObject> (new BPush);
        }
        //t += mBonusProb["TriggerP"];
        else if (r<mBonusProb["AddBombP"]+mBonusProb["AddFlameP"]+mBonusProb["FasterP"]+mBonusProb["PushP"]+mBonusProb["TriggerP"])
        {
                return Ref<GameObject> (new BTrigger);
        }
        //t += mBonusProb["SlowerP"];
        else if (r<mBonusProb["AddBombP"]+mBonusProb["AddFlameP"]+mBonusProb["FasterP"]+mBonusProb["PushP"]+mBonusProb["TriggerP"]+mBonusProb["SlowerP"])
        {
                return Ref<GameObject> (new BSlower);
        }
        //t += mBonusProb["DropP"];
        else if (r<mBonusProb["AddBombP"]+mBonusProb["AddFlameP"]+mBonusProb["FasterP"]+mBonusProb["PushP"]+mBonusProb["TriggerP"]+mBonusProb["SlowerP"]+mBonusProb["DropP"])
        {
                return Ref<GameObject> (new BDrop);
        }
        else
                return Ref<GameObject> (NULL);
}

void GameStage::AddBonus( Ref<GameObject> bonus )
{
        cast<Sprite>(mBonus)->AddChild(bonus);
}

void GameStage::EatBonus( Character* obj )
{
        Grid box = obj->GetBoundingBox();
        //int cnt = cast<Sprite>(mBonus)->NumOfChild();
		if(!mBonus.IsNull()) {
        Sprite::ChildrenContainer bonus = cast<Sprite>(mBonus)->GetAllChildren();
        int cnt = bonus.size();
        for(int i = 0;i<cnt;++i)
        {
                Ref<GameObject> child = bonus[i];
				if(!child.IsNull()) {
                Grid bBox = child->GetBoundingBox();
                if(bBox.Intersect(box))
                {
                        if(! App::Inst().AudioSys()->IsSndMute()) App::Inst().AudioSys()->PlayEffectSound(1,"eatbonus");
						if(typeid(*child) == typeid(BBombPlus))
                        {
                                obj->SetBombCnt(1);
								if(obj == &*Player()) ++mBonusCnt[0];
                        }
                        else if(typeid(*child) == typeid(BFlamePlus))
                        {
                                obj->SetPower(1);
								if(obj == &*Player()) ++mBonusCnt[1];
                        }
                        else if(typeid(*child) == typeid(BFaster))
                        {
                                //obj->SetSpeed(1.2);
								if(obj == &*Player()) ++mBonusCnt[2];

                                obj->SetSpeed(1.1);

                        }
                        else if(typeid(*child) == typeid(BTrigger))
                        {
                                obj->SetTrigBonus(true);
								if(obj == &*Player()) ++mBonusCnt[3];
                        }
                        else if(typeid(*child) == typeid(BPush))
                        {
                                obj->SetPushBonus(true);
								if(obj == &*Player()) ++mBonusCnt[4];
                        }
                        else if(typeid(*child) == typeid(BSlower))
                        {
                                obj->SetSpeed(0.67);
								if(obj == &*Player()) ++mBonusCnt[5];
                        }
                        else if(typeid(*child) == typeid(BDrop))
                        {
                                obj->SetBombCnt(-obj->GetBombCnt());
                                obj->SetTimer();
								if(obj == &*Player()) ++mBonusCnt[6];
                        }
                        child->RemoveFromParent();
                }
				}
        }
		}
}

bool GameStage::HasUwall( int row,int col )
{
        int cnt = cast<Sprite>(mUwall)->NumOfChild();
        for(int i = 0;i<cnt;++i)
        {
                Ref<GameObject> child = cast<Sprite>(mUwall)->GetChild(i);
                int tRow = child->GetBoundingBox().Row();
                int tCol = child->GetBoundingBox().Col();

                if(row == tRow && col == tCol)
                        return true;
        }
        return false;
}

void GameStage::DwallExplode( int row,int col )
{
        Sprite::ChildrenContainer dWall = cast<Sprite>(mDwall)->GetAllChildren();

        int cnt = dWall.size();
        for(int i = 0;i<cnt;++i)
        {
                Ref<GameObject> child = dWall[i];
                int tRow = child->GetBoundingBox().Row();
                int tCol = child->GetBoundingBox().Col();

                if(row == tRow && col == tCol)
                        child->RemoveFromParent();
        }
}

void GameStage::StepOnBomb( Character* obj )
{
        int cnt = cast<Sprite>(mBomb)->NumOfChild();
        Grid box = obj->GetBoundingBox();
        for(int i = 0;i<cnt;++i)
        {
                Ref<GameObject> child = cast<Sprite>(mBomb)->GetChild(i);
                Grid cBox = child->GetBoundingBox();
                if(cBox.Intersect(box))
                {
                        if(obj->HasPushBonus())
                        {
                                //LogTrace("push\n");
                                int direction = obj->GetCurState();
                                cast<Bomb>(child)->TriggerPush(direction,70.0); 
                                obj->SetPushBonus(false);
								if(obj == &*Player()) this->SetBonusCnt(4);
                        }
                        /*else
                        {
							//obj->SetLifeCnt(-1);
							obj->RemoveFromParent();
                        }*/
                }
        }
}

GameObjectContainer::ChildrenContainer GameStage::GetAllBombs()
{
        return cast<Sprite>(mBomb)->GetAllChildren();
}

void GameStage::Draw(bool is3D)
{
        if(is3D)
		{
			float lightAmbient[] = {0.7,0.7,0.7,1.0};
			float lightDiffuse[] = {0.8,0.7,0.75,1.0};
			float lightPosition[] = {75.0,10.0,65.0,0.0};
			float lmodelAmbient[] = {0.2,0.2,0.2,1.0};
			glShadeModel(GL_SMOOTH);
			glLightfv(GL_LIGHT0,GL_AMBIENT,lightAmbient);
			glLightfv(GL_LIGHT0,GL_DIFFUSE,lightDiffuse);
			glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodelAmbient);

			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);

			glEnable(GL_COLOR_MATERIAL);
			glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
			
			Stage::Draw(true);
			glDisable(GL_COLOR_MATERIAL);
			glDisable(GL_LIGHT0);
			glDisable(GL_LIGHTING);
		}
		else
			Stage::Draw(false);
}

bool GameStage::HasDwall( int row,int col )
{
        int cnt = cast<Sprite>(mDwall)->NumOfChild();
        for(int i = 0;i<cnt;++i)
        {
                Ref<GameObject> child = cast<Sprite>(mDwall)->GetChild(i);
				if(!child.IsNull()) {
                int tRow = child->GetBoundingBox().Row();
                int tCol = child->GetBoundingBox().Col();

                if(row == tRow && col == tCol)
                        return true;
				}
        }
        return false;
}

void GameStage::AddExplosion( Ref<GameObject> explosion )
{
	cast<Sprite>(mExplosion)->AddChild(explosion);
}

void GameStage::initWallMap()
{
	for(int i = 0;i<13;++i)
	{
		for(int j = 0;j<15;++j)
		{
			mWallMap[i][j] = 0;
		}
	}

	int cnt = cast<Sprite>(mUwall)->NumOfChild();
	for(int j = 0;j<cnt;++j)
	{
		Ref<GameObject> child = cast<Sprite>(mUwall)->GetChild(j);
		Grid bBox = child->GetBoundingBox();
		int row = bBox.Row();
		int col = bBox.Col();
		mWallMap[row][col] = 1;
	}

	cnt = cast<Sprite>(mDwall)->NumOfChild();
	for(int i = 0;i<cnt;++i)
	{
		Ref<GameObject> child = cast<Sprite>(mDwall)->GetChild(i);
		Grid bBox = child->GetBoundingBox();
		int row = bBox.Row();
		int col = bBox.Col();
		mWallMap[row][col] = 2;
	}
}

void GameStage::Update( float dt )
{
	Stage::Update(dt);
	App::Inst().AudioSys()->Update();
	
	mCountdownTimer -= dt;

	if(mCountdownTimer >= 0)
	{
		int cnt = cast<Sprite>(mBonusCntFont)->NumOfChild();
		for(int i = 0;i<cnt;++i)
		{
			Ref<GameObject> f = cast<Sprite>(mBonusCntFont)->GetChild(i);
			if(!f.IsNull()) cast<Font>(f)->SetContent(intToString(mBonusCnt[i]));
		}

		cast<Font>(mCountdownTimerFont)->SetContent(timeToString(mCountdownTimer));
		if(cast<Sprite>(mNpc)->NumOfChild() == 0 && (!isDead[3]))
		{
			App::Inst().AudioSys()->Stop(0);
			App::Inst().ChangeStage(7);
		}
		else if (isDead[3])
		{	
			App::Inst().AudioSys()->Stop(0);
			App::Inst().ChangeStage(8);
		}
	}
	else
	{
		App::Inst().AudioSys()->Stop(0);
		App::Inst().ChangeStage(8);
	}
	if(App::Inst().InputSys()->IsKeyDown(VK_ESCAPE))
	{
		App::Inst().AudioSys()->Stop(0);
		App::Inst().ChangeStage(0);
	}
}

std::string GameStage::timeToString( int restTime )
{
	string timeStr;

	int m = restTime/60;
	int s = restTime-m*60;

	char buf1[5];
	char buf2[5];

	itoa(m,buf1,10);
	itoa(s,buf2,10);

	if(s<10)
		timeStr = string(buf1)+ ":" + "0"+string(buf2);
	else
		timeStr = string(buf1)+ ":" + string(buf2);

	return timeStr;
}

void GameStage::CheckCharacterLife(int row,int col)
{
	//int cnt = cast<Sprite>(mNpc)->NumOfChild();
	Sprite::ChildrenContainer npcs = cast<Sprite>(mNpc)->GetAllChildren();
	int cnt = npcs.size();
	for(int i = 0;i<cnt;++i)
	{
		/*if(!isDead[i])
		{*/
			Ref<GameObject> child = npcs[i];
			Grid bBox = child->GetBoundingBox();
			if(bBox.Row() == row && bBox.Col() == col)
			{
				child->RemoveFromParent();
				LogTrace("npc %d is dead!\n",i);
				//isDead[i] = true;
				cast<Sprite>(mHUD)->GetChild(i+3)->RemoveFromParent();
				Ref<GameObject> newnpc;
				switch(i)
				{
				case 0:
					newnpc = Ref<GameObject>(new Image(DataManager::GetDataPath("Image","npc21","resource\\data.ini"),107,60));
					newnpc->SetPos(1,220,0);
					break;
				case 1:
					newnpc = Ref<GameObject>(new Image(DataManager::GetDataPath("Image","npc31","resource\\data.ini"),107,61));
					newnpc->SetPos(694,140,0);
					break;
				case 2:
					newnpc = Ref<GameObject>(new Image(DataManager::GetDataPath("Image","npc41","resource\\data.ini"),107,61));
					newnpc->SetPos(694,222,0);
					break;
				}
				cast<Sprite>(mHUD)->AddChildAt(newnpc,i+3);
				//play effect
			}
	}

	if(!isDead[3])
	{
		Ref<GameObject> player = cast<Sprite>(mPlayer)->GetChild(0);
		Grid playerBox = player->GetBoundingBox();
		if(playerBox.Row() == row && playerBox.Col() == col)
		{
			//player->RemoveFromParent();
			//play effect
			isDead[3] = true;
		}
	}
}

std::string GameStage::intToString( int cnt )
{
	string str;
	char buf1[5];

	itoa(cnt,buf1,10);
	str = string(buf1);

	return str;
}

void GameStage::SetBonusCnt( int bonusId )
{
	--mBonusCnt[bonusId];
}
