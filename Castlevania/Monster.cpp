#include "Monster.h"

void Monster::Update(DWORD dt)
{
	GameObject::Update(dt);
	vx = MONSTER_SPEED;


	if (vx < 0 && x < 0) 
	{
		x = 0;
		vx = -vx;
	}

	if (vx > 0 && x > 290) 
	{
		x = 290;
		vx = -vx;
	}
}

void Monster::Render()
{
	int ani;
	ani = MONSTER_ANI_WLKING;
	

}

void Monster::SetState(int state)
{
	
}
