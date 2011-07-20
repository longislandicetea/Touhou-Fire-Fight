#include "GameStage.h"

#include <iostream>
#include <cstdlib>
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
#include "Image.h"
#include "Image3D.h"
#include "DataManager.h"
#include"gl/GL.h"
#include "App.h"

#include "vector"

Ref<GameObject> GameStage::CurrentMap()
{
        return mCurrentMap;
}

GameStage::GameStage( Ref<GameObject> map ) 
{
        //read map
        mCurrentMap = map;
        mBonusProb = cast<Map>(mCurrentMap)->GetBonusProb();

        std::map< std::string,Ref<GameObject> > info = cast<Map>(mCurrentMap)->Parse();
        mDwall = info["dwall"];
        mUwall = info["uwall"];
        mNpc = info["npc"];
        mPlayer = info["player"];
        mFloor = info["decoration"];
        mBomb  = Ref<GameObject>(new Sprite);
        mBonus = Ref<GameObject>(new Sprite);
        mHUD = Ref<GameObject> (new Sprite);
		mExplosion = Ref<GameObject> (new Sprite);

		//mPlayer->SetX(GetX()-5);
        //set gamestage
        //this->AddChild(mFloor);
        this->AddChild(mDwall);
        this->AddChild(mUwall);
        this->AddChild(mNpc);
        this->AddChild(mPlayer);
        this->AddChild(mBomb);
        this->AddChild(mBonus);
        this->AddChild(mHUD);
		this->AddChild(mExplosion);

        //hud test
		Ref<GameObject> bg1(new Image(DataManager::GetDataPath("Image","bg1","resource\\data.ini"),800,600));
		cast<Sprite>(mHUD)->AddChild(bg1);
		
		Ref<GameObject> image(new Image(DataManager::GetDataPath("Image","tmp","resource\\data.ini"),128,128));
		cast<Sprite>(mHUD)->AddChild(image);

		Ref<GameObject> time(new Font("Comic Sans MS",28,"just a test"));
		cast<Font>(time)->SetPos2D(390,56);
		cast<Sprite>(mHUD)->AddChild(time);

		App::Inst().AudioSys()->PlayStream(0,"background");

		initWallMap();
}

GameStage::~GameStage()
{
        std::cout<<"gamestage released"<<std::endl;
}

Ref<GameObject> GameStage::Player()
{
        return mPlayer;
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
		Grid bBox = child->GetBoundingBox();
		if(bBox.Intersect(box))
		{
			return false;
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
        Sprite::ChildrenContainer bonus = cast<Sprite>(mBonus)->GetAllChildren();
        int cnt = bonus.size();
        for(int i = 0;i<cnt;++i)
        {
                Ref<GameObject> child = bonus[i];
                Grid bBox = child->GetBoundingBox();
                if(bBox.Intersect(box))
                {
                        if(typeid(*child) == typeid(BBombPlus))
                        {
                                obj->SetBombCnt(1);
                        }
                        else if(typeid(*child) == typeid(BFlamePlus))
                        {
                                obj->SetPower(1);
                        }
                        else if(typeid(*child) == typeid(BFaster))
                        {
                                obj->SetSpeed(1.5);
                        }
                        else if(typeid(*child) == typeid(BTrigger))
                        {
                                obj->SetTrigBonus(true);
                        }
                        else if(typeid(*child) == typeid(BPush))
                        {
                                obj->SetPushBonus(true);
                        }
                        else if(typeid(*child) == typeid(BSlower))
                        {
                                obj->SetSpeed(2/3);
                        }
                        else if(typeid(*child) == typeid(BDrop))
                        {
                                obj->SetBombCnt(-obj->GetBombCnt());
                                obj->SetTimer();
                        }
                        child->RemoveFromParent();
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
                                LogTrace("push\n");
                                int direction = obj->GetCurState();
                                cast<Bomb>(child)->TriggerPush(direction,70.0); 
                                obj->SetPushBonus(false);
                        }
                        else
                        {
                                //dead
                        }
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
			;
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
                int tRow = child->GetBoundingBox().Row();
                int tCol = child->GetBoundingBox().Col();

                if(row == tRow && col == tCol)
                        return true;
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
}