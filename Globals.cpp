#include "Globals.h"

SCREENINFO s_Screen;

cl_clientfunc_t* pClient = nullptr;
cl_enginefunc_t* pEngine = nullptr;
engine_studio_api_t* pStudio = nullptr;
r_studio_interface_t* pStudioAPI = nullptr;
IGameConsole* pConsole = nullptr;
IGameUI* pGameUI = nullptr;

cl_clientfunc_t Client;
cl_enginefunc_t Engine;
engine_studio_api_t Studio;
r_studio_interface_t StudioAPI;

PUserMsg pUserMsgBase;
DWORD dwSpeedPtr, pSpeed;
playermove_t* pPlayerMove;

Drawing Paint;
HGUI GUI;

bool keys[256], keysState[256], keysBlock[256];
float SpeedFac;

Cvars Cvar;
Utilities Utility;
Players Player[33];
Locals Local;
Functions Function;
btn_bits BtnBits;

Color white = { 255, 255, 255, 255 };