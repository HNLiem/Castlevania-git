#pragma once
#include "GameObject.h"


#define SIMON_WALKING_SPEED		0.07f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_GRAVITY			0.002f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_FIGHT			400
#define SIMON_STATE_JUMP_FIGHT		500
#define SIMON_STATE_SIT				600
#define SIMON_STATE_SIT_FIGHT		700


#define SIMON_ANI_IDLE_RIGHT		0
#define SIMON_ANI_IDLE_LEFT			1
#define SIMON_ANI_WALKING_RIGHT		2
#define SIMON_ANI_WALKING_LEFT		3
#define SIMON_ANI_FIGHT_RIGHT		4
#define SIMON_ANI_FIGHT_LEFT		5
#define SIMON_ANI_JUMP_RIGHT		6
#define SIMON_ANI_JUMP_LEFT			7
#define SIMON_ANI_SIT_RIGHT			8
#define SIMON_ANI_SIT_LEFT			9
#define SIMON_ANI_SIT_FIGHT_RIGHT	10
#define SIMON_ANI_SIT_FIGHT_LEFT	11
#define SIMON_BBOX_WIDTH			30
#define SIMON_BBOX_HEIGHT			60
#define SIMON_UNTOUCHABLE_TIME		5000
class Simon:public GameObject
{
	int untouchable;
	DWORD untouchable_start;
	bool finish;
public:
	virtual void Update(DWORD dt , vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	bool GetFinish() { return finish; }
};

