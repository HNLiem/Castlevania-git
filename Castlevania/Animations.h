#pragma once
#include<Windows.h>
#include<unordered_map>
#include<d3dx9.h>
#include"Animation.h"
class Animations
{
private:
	static Animations *_instance;
	unordered_map<int, LPANIMATION> animations;
public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);
	static Animations * GetInstance();
};
