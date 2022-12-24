#pragma once

#include "Misc.h"
#include "GUI.h"
#include "Utilities.h"
#include "Functions.h"
#include "Strings.h"

#define PUBLIC 1

extern SCREENINFO s_Screen;

extern cl_clientfunc_t* pClient;
extern cl_enginefunc_t* pEngine;
extern engine_studio_api_t* pStudio;
extern r_studio_interface_t* pStudioAPI;
extern IGameConsole* pConsole;

extern cl_clientfunc_t Client;
extern cl_enginefunc_t Engine;
extern engine_studio_api_t Studio;
extern r_studio_interface_t StudioAPI;

extern PUserMsg pUserMsgBase;
extern DWORD dwSpeedPtr, pSpeed;
extern playermove_t* pPlayerMove;

extern bool keys[256], keysState[256], keysBlock[256];
extern float SpeedFac;

struct Cvars
{
	struct menu
	{
		Color BgColor, FColor, SColor, TColor, TxtColor, TxtColor2;
	}Menu;

	struct aimbot
	{
		bool Enabled, FriendlyFire, DrawFOV;
		float FOV;
	}Aim;

	struct chams
	{
		bool Enabled, Alpha;
		Color FRColor, ENColor;
	}Chams;

	struct visual
	{
		bool NoInvise, NoGlow, NoSmoke, NoFlash, NoFog, Lambert, FullBright, NoCostumes, WallHack, CustomCrosshair;
	}Visual;

	struct misc
	{
		bool ShowSpeed, Hung, GS;
		float SpeedFac;
	}Misc;
};
extern Cvars Cvar;

struct Players
{
	int ID, Team;
	float FOV;
	Vector Hitbox[11], Origin;
	bool Updated, Visible, IsHacker;
};
extern Players Player[33];

struct Locals
{
	int ID, Team, FOV, GroundAngle;
	bool Alive, Hung;
	Vector Eye;
	float GroundSpeed, Height;
};
extern Locals Local;

typedef struct btn_bits
{
	DWORD inJump, inDuck;
};
extern btn_bits BtnBits;

extern Color white;