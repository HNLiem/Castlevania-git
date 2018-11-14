#include "Torch.h"

void Torch::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + TORCH_BBOX_WIDTH;
	bottom = y + TORCH_BBOX_HEIGHT;
}

void Torch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
	x += dx;
	y += dy;
}

void Torch::Render()
{
	int ani = TORCH_ANI;
	if (state == TORCH_STATE_DIE)
	{
		ani = TORCH_ANI_DIE;
	}
	animations[ani]->Render(x,y);
}

void Torch::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case TORCH_STATE_DIE:
		state = TORCH_ANI_DIE;
		break;
	case TORCH_STATE_FIRE:
		state = TORCH_ANI;
	}
}
