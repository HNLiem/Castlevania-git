#pragma once
#include<Windows.h>
#include<d3dx9.h>
#include<unordered_map>
#include"Sprite.h"

class Sprites
{
private:
	static Sprites *_instance;
	unordered_map<int, LPSPRITE> sprites;
public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, D3DXVECTOR2 position = { 0, 0 });
	LPSPRITE Get(int id);
	static Sprites * GetInstance();
};

