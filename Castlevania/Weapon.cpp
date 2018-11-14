#include "Weapon.h"
#include"Game.h"
#include"GameObject.h"
#include"Torch.h"
#include<algorithm>

void Weapon::Update(DWORD dt,Simon *simon,Torch *torch)
{
	GameObject::Update(dt);
	SetPosition(simon);
		if (this->AABBx(torch)==true)
		{
			if (torch->GetState() != TORCH_STATE_DIE)
			{
				torch->SetState(TORCH_STATE_DIE);
			}
		}	
}

void Weapon::Render(Simon *simon)
{
	if (state == WEAPON_STATE_FIGHT)
	{
		if (simon->Getnx() > 0)
		{
			ani = WEAPON_ANI_FIGHT_LEVEL_A_RIGHT;
		}
		else
		{
			ani = WEAPON_ANI_FIGHT_LEVEL_A_LEFT;
		}
		animations[ani]->Render(x, y);
		box = animations[ani]->GetBoolBox();
		RenderBoundingBox();
	
	}
	
	
}

void Weapon::SetState(int state,Simon *simon)
{
	GameObject::SetState(state);
	switch (state)
	{
	case WEAPON_STATE_FIGHT:

		/*if (simon->Getnx() > 0)
		{
			state = WEAPON_ANI_FIGHT_LEVEL_A_RIGHT;
		}
		else
		{
			state = WEAPON_ANI_FIGHT_LEVEL_A_LEFT;
		}*/
		//}

		break;
	}
}

void Weapon::SetPosition(Simon * simon)
{
	this->x = simon->Getx();
	this->y = simon->Gety();
}

void Weapon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{	
	if (state == WEAPON_STATE_FIGHT && box == true)
	{
		
			
			if (ani == WEAPON_ANI_FIGHT_LEVEL_A_RIGHT )
			{
				
				left = x + 35;
				top = y + 9;
				right = x + WEAPON_BBOX_WIDTH + 35;
				bottom = y + WEAPON_BBOX_HEIGHT + 9;
			}
			else
			{


				left = x - 40;
				top = y + 10;
				right = x + WEAPON_BBOX_WIDTH;
				bottom = y + WEAPON_BBOX_HEIGHT;


			}
		
		
		
	}
}



