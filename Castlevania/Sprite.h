#pragma once
#include <Windows.h>
#include <d3dx9.h>
using namespace std;
class Sprite
{
private:
	int id;
	int left;
	int top;
	int right;
	int bottom;
	D3DXVECTOR2 position;
	LPDIRECT3DTEXTURE9 texture;
	int isFlippedHorizontally;
public:
	Sprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, D3DXVECTOR2 position = { 0, 0 });
	void Draw(float x, float y,int alpha=255);
	int Getid() { return id; };
	~Sprite();
};
typedef Sprite * LPSPRITE;

