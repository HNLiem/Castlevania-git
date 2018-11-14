#include "Sprite.h"
#include"Game.h"

Sprite::Sprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex,D3DXVECTOR2 position )
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
	this->position = position;
}

void Sprite::Draw(float x, float y, int alpha)
{
	Game*game = Game::GetInstance();
	game->Draw(x+position.x, y+position.y, texture, left, top, right, bottom, alpha);
}


Sprite::~Sprite()
{
}
