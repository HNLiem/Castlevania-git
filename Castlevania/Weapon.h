#pragma once
#include "GameObject.h"
#include "Simon.h"
#include"Torch.h"
#define WEAPON_STATE_FIGHT 0
#define WEAPON_STATE_IDLE 1
#define WEAPON_ANI_FIGHT_LEVEL_A_RIGHT   12
#define WEAPON_ANI_FIGHT_LEVEL_A_LEFT	 13
#define WEAPON_BBOX_WIDTH				45
#define WEAPON_BBOX_HEIGHT				16
#define WEAPON_UNTOUCHABLE_TIME 5000

class Weapon:public GameObject
{
private:
	int level;
	int untouchable;
	DWORD untouchable_start;
	float xsimon, ysimon;
	int ani;
	bool box;
public:
	Weapon() :GameObject()
	{
		untouchable = 0;
	}
	virtual void Update(DWORD dt,Simon *simon ,Torch *torch);
	virtual void Render(Simon *simon);
	void SetState(int state,Simon *simon);
	void SetLevel(int l=1) { this->level = l; }
	void SetPosition(Simon *simon);
	
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

