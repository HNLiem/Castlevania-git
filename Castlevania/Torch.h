#pragma once
#include"GameObject.h"
#define TORCH_BBOX_WIDTH	32
#define TORCH_BBOX_HEIGHT	32

#define TORCH_STATE_FIRE	100
#define TORCH_STATE_DIE		200
#define TORCH_ANI			50
#define TORCH_ANI_DIE		51
class Torch:public GameObject
{
public:
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
};

