﻿#include "Game.h"
Game * Game::_instance = NULL;


void Game::InitKeyboard(LPKEYEVENTHANDLER handler)
{
	HRESULT
		hr = DirectInput8Create
		(
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&di, NULL
		);

	if (hr != DI_OK)
	{
		return;
	}

	hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);
	if (hr != DI_OK)
	{
		return;
	}

	hr = didv->SetDataFormat(&c_dfDIKeyboard);
	hr = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; 

	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = didv->Acquire();
	if (hr != DI_OK)
	{
		return;
	}

	this->keyHandler = handler;
}

void Game::Init(HWND hWnd)
{
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	this->hWnd = hWnd;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(hWnd, &r);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (d3ddv == NULL)
	{
		OutputDebugString(L"[ERROR] CreateDevice failed\n");
		return;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(d3ddv, &spriteHandler);

	OutputDebugString(L"[INFO] InitGame done;\n");
}

void Game::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha, int isFlippedHorizontally)
{
	D3DXVECTOR3 p(x-this->camx, y-this->camy, 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;

	D3DXMATRIX mPre;
	D3DXMATRIX mFlipped;
	spriteHandler->GetTransform(&mPre);

	if (isFlippedHorizontally == 1) {
		spriteHandler->GetTransform(&mFlipped);
		D3DXMatrixScaling(&mFlipped, -1.0f, 1.0f, .0f);
		spriteHandler->SetTransform(&mFlipped);
		p.x = -p.x - (right - left);
	}

	spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	spriteHandler->SetTransform(&mPre);
}

int Game::IsKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) > 0;
}

void Game::ProcessKeyboard()
{
	HRESULT hr;
	hr = didv->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(hr))
	{
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv->Acquire();
			if (h == DI_OK)
			{
			}
			else 
			{ 
				return; 
			}
		}
		else
		{
			return;
		}
	}

	keyHandler->KeyState((BYTE *)&keyStates);

	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		return;
	}

	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
		{
			keyHandler->OnKeyDown(KeyCode);
		}
		else
		{
			keyHandler->OnKeyUp(KeyCode);
		}
	}
}

Game * Game::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new Game();
	}
	return _instance;
}
// ml,mt,mr,mb :left top right bottom cua object
// sl,st,sr,sb: left top right bottom cua other
// dx,dy,nx, ny cua object m
void Game::SweptAABB(float ml, float mt, float mr, float mb, float dx, float dy, float sl, float st, float sr, float sb, float & t, float & nx, float & ny)
{
	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	t = -1.0f;			

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;
	// tao mot hinh chu nhat moi voi tao do x,y cao dai
	
	//float bl, bt, br, bb;
	
	/*if (dx > 0)
	{
		// van toc lon hon 0
		// left=left vat
		bl = ml;
	}
	else
	{
		// left=left+vantoc x
		bl = ml + dx;
	}
	if (dy > 0)
	{
		bt = mt;
	}
	else
	{
		bt = mt + dy;
	}
	if (dx > 0)
	{
		br = mr+dx;
	}
	else
	{
		br = mr;
	}
	if (dy > 0)
	{
		bb = mb+dy;
	}
	else
	{
		bb = mb;
	}*/
	if (br < sl || bl > sr || bb < st || bt > sb)
	{
		return;
	}


	/*if (dx == 0 && dy == 0)
	{
		return;
	}*/// moving object is not moving > obvious no collision
	// s=other m object simon roi
	//dxEntry, dyEntry: là khoảng cách cần đi để các bắt đầu va chạm.
	//dxExit, dyExit: là khoảng cách cần đi kể từ lúc này để khi hết va chạm.
	// d=v cua aVinh
	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}


	if (dy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}
	// khuc nay tim thoi gian bat dau va ket thuc va cham
	//tg=s/v
	if (dx == 0)
	{
		tx_entry = -99999999999;
		tx_exit = 99999999999;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999999999;
		ty_exit = 99999999999;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}


	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f)
	{
		return;
	}
	// thời gian va chạm là thời gian lớn nhất của 2 trục (2 trục phải cùng tiếp xúc thì mới va chạm)
	t_entry = max(tx_entry, ty_entry);
	// thời gian hết va chạm là thời gian của 2 trục, (1 cái ra khỏi là object hết va chạm)
	t_exit = min(tx_exit, ty_exit);

	// thoi gian can de va cham lon hon thoi gian thoat va cham
	// return khong set nua
	if (t_entry > t_exit)
	{
		return;
	}

	t = t_entry;
	// tim huoong va cham
	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		//dx > 0 ? nx = -1.0f : nx = 1.0f;
		if (dx > 0)
		{
			nx = -1.0f; // va cham ben phai
		}
		else
		{
			nx = 1.0f;// va cham ben trai
		}
	}
	else
	{
		nx = 0.0f;
		//dy > 0 ? ny = -1.0f : ny = 1.0f;
		if (dy > 0)
		{
			ny = -1.0f;// va cham ben tren
		}
		else
		{
			ny = 1.0f;// va cham ben duoi
		}
	}
}
// s la other 
bool Game::AABB(float ml, float mt, float mr, float mb, float sl, float st, float sr, float sb)
{
	float left = sl - mr;
	float top=sb-mt;
	float right = sr - ml;
	float bottom = st - mb;
	return !(left > 0 || right < 0 || top < 0 || bottom > 0);

}



Game::~Game()
{
	if (spriteHandler != NULL)
	{
		spriteHandler->Release();
	}
	if (backBuffer != NULL)
	{
		backBuffer->Release();
	}
	if (d3ddv != NULL)
	{
		d3ddv->Release();
	}
	if (d3d != NULL)
	{
		d3d->Release();
	}
}
