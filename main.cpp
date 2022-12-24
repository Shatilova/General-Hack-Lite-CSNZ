#include "Misc.h"
#include "PEB.h"
#include "Engine.h"
#include "Render.h"

HWND hWnd;
WNDPROC WndProcBackup;

LRESULT CALLBACK hk_WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		keys[VK_LBUTTON] = true;
		break;
	case WM_LBUTTONUP:
		keys[VK_LBUTTON] = false;
		break;
	case WM_RBUTTONDOWN:
		keys[VK_RBUTTON] = true;
		break;
	case WM_RBUTTONUP:
		keys[VK_RBUTTON] = false;
		break;
	case WM_KEYDOWN:
		keys[wParam] = true;
		break;
	case WM_KEYUP:
		keys[wParam] = false;
		break;
	default: break;
	}

	//mouseWheel = GET_WHEEL_DELTA_WPARAM(wParam);

	return CallWindowProcA(WndProcBackup, hwnd, uMsg, wParam, lParam);
}

void SetupHook()
{
	offset.GetGameModules();

	pClient = (cl_clientfunc_t*)offset.Client();
	pEngine = (cl_enginefunc_t*)offset.Engine();
	pStudio = (engine_studio_api_t*)offset.Studio();
	pConsole = (IGameConsole*)(CaptureInterface(CaptureFactory(GAMEUI_DLL), GAMECONSOLE003));
	//pGameUI = (IGameUI*)(CaptureInterface(CaptureFactory(GAMEUI_DLL), GAMEUI_INTERFACE_VERSION));
	pStudioAPI = *(r_studio_interface_t**)offset.StudioAPI();
	pUserMsgBase = (PUserMsg)offset.UserMsgBase();
	pSpeed = (DWORD)offset.SpeedPtr();
	pPlayerMove = (playermove_t*)offset.PlayerMove();

	offset.HookUserMsgs();
	offset.ClientKeys();
	
	memcpy(&Engine, pEngine, sizeof(cl_enginefunc_t));
	memcpy(&Studio, pStudio, sizeof(engine_studio_api_t));
	memcpy(&StudioAPI, pStudioAPI, sizeof(r_studio_interface_t));

	pEngine->HUD_Redraw = HUD_Redraw;
	pEngine->HUD_AddEntity = HUD_AddEntity;
	pEngine->CL_CreateMove = CL_CreateMove;
	pStudio->StudioSetupLighting = StudioSetupLighting;
	pStudio->StudioEntityLight = StudioEntityLight;
	pStudioAPI->StudioDrawPlayer = StudioDrawPlayer;
	pStudioAPI->StudioDrawModel = StudioDrawModel;

	hWnd = FindWindowA(NULL, GAME_NAME);
	WndProcBackup = (WNDPROC)SetWindowLongA(hWnd, GWL_WNDPROC, (LONG_PTR)& hk_WndProc);

	pConsole->Clear();
	pConsole->Activate();
	
	//pConsole->DPrintf("Client - 0x%X\nEngine - 0x%X\nStudio - 0x%X\nStudioAPI - 0x%X\nUserMsgBase - 0x%X\nSpeed - 0x%X\nPlayerMove - 0x%X\ninJump - 0x%X\ninDuck - 0x%X\n\n", pClient, pEngine, pStudio, pStudioAPI, pUserMsgBase, pSpeed, pPlayerMove, BtnBits.inJump, BtnBits.inDuck);
	pConsole->DPrintf(ENTRY_MSG, Engine.pfnGetCvarPointer(NAME)->string);
	pEngine->pfnPlaySoundByName(START_SOUND, 1);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL , DWORD fdwReason , LPVOID lpReserved)
{
	HANDLE hThread = 0;

	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hinstDLL);//Shouldn't use hiding API on this function. The hacc may not work then 
		UnlinkModuleFromPEB(hinstDLL);

		if (RemoveHeader(hinstDLL))//If you will protect the compiled DLL using protectors/packers, you should remove RemoveHeader func call
		{
			hThread = CreateThread(0 , 0 , (LPTHREAD_START_ROUTINE)SetupHook , 0 , 0 , 0);
			HideThread(hThread);
		}
	}

	return TRUE;
}