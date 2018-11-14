#include<windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include"Game.h"
#include"GameObject.h"
#include"Textures.h"
#include"Simon.h"
#include"Animation.h"
#include"Animations.h"
#include"Sprite.h"
#include"Sprites.h"
#include"Weapon.h"
#include"Monster.h"
#include"Brick.h"
#include"Torch.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Castlevania"
#define BACKGROUND_COLOR D3DCOLOR_XRGB(200, 200, 255)
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAX_FRAME_RATE 120
#define ID_TEX_SIMON 0
#define ID_TEX_SIMON1 1
#define ID_TEX_SIMON2 2
#define ID_TEX_WEAPON 3
#define ID_TEX_WEAPON1 4
#define ID_TEX_TORCH   5
#define ID_TEX_MISC 20
// xu ly va cham hai vat va cham khong van toc su dung AABB
Game *game;
Simon *simon;
Weapon *weapon;
Torch *torch;
vector<LPGAMEOBJECT> objects;

int a = 0;

class SampleKeyHander : public KeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

SampleKeyHander * keyHandler;

void SampleKeyHander::OnKeyDown(int KeyCode)
{
	
	if( DIK_K  )
	{
		if (simon->GetFinish() == false)
		{
			simon->SetState(SIMON_STATE_FIGHT);
			weapon->SetState(WEAPON_STATE_FIGHT, simon);
		}
	}
}

void SampleKeyHander::OnKeyUp(int KeyCode)
{
	
}

void SampleKeyHander::KeyState(BYTE *states)
{
	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_F))
		{
			simon->SetState(SIMON_STATE_IDLE);
			simon->SetState(SIMON_STATE_FIGHT);
			weapon->SetState(WEAPON_STATE_FIGHT, simon);
		}
		else
		{
			simon->SetState(SIMON_STATE_WALKING_RIGHT);
			weapon->SetState(WEAPON_STATE_IDLE, simon);
		}
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_F))
		{
			simon->SetState(SIMON_STATE_IDLE);
			simon->SetState(SIMON_STATE_FIGHT);
			weapon->SetState(WEAPON_STATE_FIGHT, simon);
		}
		else
		{
			simon->SetState(SIMON_STATE_WALKING_LEFT);
			weapon->SetState(WEAPON_STATE_IDLE, simon);
		}
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		if (game->IsKeyDown(DIK_F))
		{
			simon->SetState(SIMON_STATE_SIT_FIGHT);
		}
		else
		{
			simon->SetState(SIMON_STATE_SIT);
		}
	}
	else if(game->IsKeyDown(DIK_F))
	{
		simon->SetState(SIMON_STATE_FIGHT);
		weapon->SetState(WEAPON_STATE_FIGHT,simon);
	}
	else if(game->IsKeyDown(DIK_SPACE))
	{
		simon->SetState(SIMON_STATE_JUMP);
		weapon->SetState(WEAPON_STATE_IDLE,simon);
	}
	
	else
	{
			simon->SetState(SIMON_STATE_IDLE);
			weapon->SetState(WEAPON_STATE_IDLE, simon);
	}
}
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
void LoadResources()
{
	Textures * textures = Textures::GetInstance();
	textures->Add(ID_TEX_SIMON, L"Resources\\simon1.png", D3DCOLOR_XRGB(255, 0, 255));
	//Textures * textures1 = Textures::GetInstance();
	textures->Add(ID_TEX_SIMON1, L"Resources\\simon.png", D3DCOLOR_XRGB(255, 0, 255));
	//Textures * texture3 = Textures::GetInstance();
	textures->Add(ID_TEX_WEAPON, L"Resources\\morningstar1.png", D3DCOLOR_XRGB(255, 0, 255));
	//Textures * textures4 = Textures::GetInstance();
	textures->Add(ID_TEX_WEAPON1, L"Resources\\morningstar.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_MISC, L"Resources\\ground\\2.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_TORCH, L"Resources\\ground\\0.png", D3DCOLOR_XRGB(255, 0, 255));
	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);
	LPDIRECT3DTEXTURE9 texSimon1 = textures->Get(ID_TEX_SIMON1);
	LPDIRECT3DTEXTURE9 texWeapon = textures->Get(ID_TEX_WEAPON);
	LPDIRECT3DTEXTURE9 texWeapon1 = textures->Get(ID_TEX_WEAPON1);
	LPDIRECT3DTEXTURE9 texbrick = textures->Get(ID_TEX_MISC);
	LPDIRECT3DTEXTURE9 textorch = textures->Get(ID_TEX_TORCH);
	// gach
	sprites->Add(20001, 0, 0, 32, 32, texbrick);
	// ngon duoc
	sprites->Add(20002, 0, 0, 32, 64, textorch);
	sprites->Add(20003, 32, 0, 62, 64, textorch);
	// khong duoc
	sprites->Add(20004, 0, 0, 0, 0, textorch);
	//di phai
	sprites->Add(10001, 314, 4, 344, 64, texSimon);
	sprites->Add(10002, 378, 2, 402, 64, texSimon);
	sprites->Add(10003, 436, 4, 467, 64, texSimon);
	// danh phai
	sprites->Add(10004, 120, 4, 168, 64, texSimon);
	sprites->Add(10005, 74, 4, 107, 64, texSimon);
	sprites->Add(10006, 15, 6, 58, 64, texSimon);
	// nhay phai
	sprites->Add(10008, 196, 1, 228, 47, texSimon);
	sprites->Add(10009, 196, 1, 228, 47, texSimon);
	// roi ben phai
	sprites->Add(10011, 488, 17, 504, 66, texWeapon, { -9,14 });
	sprites->Add(10012, 328, 12, 360, 50, texWeapon, { -30,8 });
	sprites->Add(10013, 243, 16, 288, 32, texWeapon, { 35,9 });
	// ngoi ben phai
	sprites->Add(10014, 196, 1, 228, 47, texSimon, {0,15});
	// ngoi danh ben phai
	sprites->Add(100015, 0, 67, 48, 113, texSimon);
	sprites->Add(100016, 437, 113, 469, 178, texSimon);
	sprites->Add(100017, 375, 135, 419, 178, texSimon);
	//di trai
	sprites->Add(11001, 136, 4, 166, 64, texSimon1);
	sprites->Add(11002, 78, 2, 102, 64, texSimon1);
	sprites->Add(11003, 12, 4, 44, 64, texSimon1);
	// danh trai
	sprites->Add(11004, 421, 6, 464, 64, texSimon1);
	sprites->Add(11005, 373, 4, 405, 64, texSimon1);
	sprites->Add(11006, 311, 4, 360, 64, texSimon1);
	// nhay trai
	sprites->Add(11007, 136, 4, 166, 64, texSimon1);
	sprites->Add(11008, 252, 0, 284, 47, texSimon1);
	sprites->Add(11009, 252, 0, 284, 47, texSimon1);
	sprites->Add(11010, 136, 4, 166, 64, texSimon1);
	//danh roi trai
	sprites->Add(11011, 136, 18, 152, 66, texWeapon1, { 41,15 });
	sprites->Add(11012, 280, 11, 312, 50, texWeapon1, { 28,8 });
	sprites->Add(11013, 352, 15, 398, 32, texWeapon1, { -40,10 });
	// ngoi ben trai
	sprites->Add(11014, 252, 0, 284, 47, texSimon1, {0,15});
	// ngoi danh ben trai
	sprites->Add(110015, 432, 67, 0, 113, texSimon);
	sprites->Add(110016, 10, 113, 43, 179, texSimon);
	sprites->Add(110017, 61, 135, 105, 179, texSimon);
	LPANIMATION ani;
	//dung quay mat ve ben phai
	ani = new Animation(100);
	ani->Add(10001);
	animations->Add(400, ani);
	// dung quay mat ve ben trai
	ani = new Animation(100);
	ani->Add(11001);
	animations->Add(401, ani);
	// di ben phai
	ani = new Animation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(500, ani);
	// di ben trai
	ani = new Animation(100);
	ani->Add(11001);
	ani->Add(11002);
	ani->Add(11003);
	animations->Add(501, ani);
	 // danh ben phai
	ani = new Animation(100);
	ani->Add(10004);
	ani->Add(10005);
	ani->Add(10006);
	animations->Add(600,ani);
	// danh ben trai
	ani = new Animation(100);
	ani->Add(11006);
	ani->Add(11005);
	ani->Add(11004);
	animations->Add(601,ani);
	// nhay ben phai
	ani = new Animation(100);
	ani->Add(10008);
	ani->Add(10009);
	animations->Add(700, ani);
	// nhay ben trai
	ani = new Animation(100);
	ani->Add(11008);
	ani->Add(11009);
	animations->Add(701, ani);
	// ngoi ben phai
	ani = new Animation(100);
	ani->Add(10014);
	animations->Add(800, ani);
	//ngoi ben trai
	ani = new Animation(100);
	ani->Add(11014);
	animations->Add(801, ani);
	// ngoi danh ben phai
	ani = new Animation(100);
	ani->Add(10015);
	ani->Add(10016);
	ani->Add(10017);
	animations->Add(900, ani);
	// ngoi danh ben trai
	ani = new Animation(100);
	ani->Add(11015);
	ani->Add(11016);
	ani->Add(11017);
	animations->Add(901, ani);


	simon = new Simon();
	Simon::AddAnimation(400);	// dung ben phai	
	Simon::AddAnimation(401);	//dung ben trai	
	Simon::AddAnimation(500);	// di ben phai
	Simon::AddAnimation(501);	// di ben trai
	Simon::AddAnimation(600);	// danh ben phai
	Simon::AddAnimation(601);	// danh ben trai
	Simon::AddAnimation(700);
	Simon::AddAnimation(701);
	Simon::AddAnimation(800);	
	Simon::AddAnimation(801);	
	Simon::AddAnimation(900);
	Simon::AddAnimation(901);
	simon->SetPosition(50.0f,0);
	objects.push_back(simon);
	ani = new Animation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(1000, ani);
	ani = new Animation(100);
	ani->Add(11011);
	ani->Add(11012);
	ani->Add(11013);
	animations->Add(1001, ani);
	weapon = new Weapon();
	Weapon::AddAnimation(1000);
	Weapon::AddAnimation(1001);
	weapon->SetPosition(simon);
	
	ani = new Animation(100);
	ani->Add(20001);
	animations->Add(1002, ani);
	//objects.push_back(weapon);
	
	
	for (int i = 0; i < 30; i++)
	{
		Brick *brick = new Brick();
		brick->AddAnimation(1002);
		brick->SetPosition(i * 32.0f, SCREEN_HEIGHT-80);
		objects.push_back(brick);
		
	}

	ani = new Animation(100);
	ani->Add(20002);
	ani->Add(20003);
	animations->Add(1003, ani);
	ani = new Animation(100);
	ani->Add(20004);
	animations->Add(1004, ani);
	torch = new Torch();
	Torch::AddAnimation(1003);
	Torch::AddAnimation(1004);
	torch->SetPosition(50,340);
	//objects.push_back(torch);
}
void Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// game->SetPosition(cx - SCREEN_WIDTH / 2, 0);
}
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, 
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				done = 1;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();
		DWORD dt = now - frameStart;
		if (dt >= tickPerFrame)
		{
			frameStart = now;
			game->ProcessKeyboard();
			Update(dt);
			Render();
		}
		else 
		{
			Sleep(tickPerFrame - dt);
		}
	}
	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = Game::GetInstance();
	game->Init(hWnd);
	keyHandler = new SampleKeyHander();
	game->InitKeyboard(keyHandler);
	LoadResources();
	//SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	Run();
	return 0;
}