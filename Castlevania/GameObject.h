#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include"Animation.h"
#include"Animations.h"
using namespace std;

#define ID_TEX_BBOX -100		

class GameObject;
typedef GameObject * LPGAMEOBJECT;

struct CollisionEvent;
typedef CollisionEvent * LPCOLLISIONEVENT;
struct CollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};
class GameObject
{
protected:
	float x, y;
	float vx, vy;
	float dx, dy;
	int nx;
	int state;
	DWORD dt;
	static vector<LPANIMATION> animations;
public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	virtual void SetState(int state) { this->state = state; }
	int GetState() { return this->state; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	float Getx() { return this->x; }
	float Gety() { return this->y; }
	int Getnx() { return this->nx; }
	static void AddAnimation(int aniId);
	void RenderBoundingBox();

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	bool AABBx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	// ham loc va cham
	void FilterCollision
	(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);
	GameObject();
virtual	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
virtual	void Render();
// ve khung gioi hsn
virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	~GameObject();
};

