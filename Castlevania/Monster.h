#pragma once
#include"GameObject.h"
#include"Game.h"
#define MONSTER_SPEED 0.15f
#define MONSTER_GRAVITY	0.07f
#define MONSTER_ANI_WLKING 11
class Monster:public GameObject
{
public:
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
};

