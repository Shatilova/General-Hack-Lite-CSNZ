#include "Engine.h"

int i_LoadText = 50;
bool b_FirstFrame = true;
void smoke_event(event_args_s*) {}
static screenfade_t sf = { 0.0, 0.0, 0.0, 0, 0, 0, 0, 0 };

int HUD_Redraw()
{
	if (b_FirstFrame)
	{
		s_Screen.iSize = sizeof(SCREENINFO);
		Engine.pfnGetScreenInfo(&s_Screen);
		Utility.LoadCFG();
		b_FirstFrame = false;
	}

	if (i_LoadText > -1) i_LoadText--;
	if (i_LoadText > 0) Paint.InitText(); //This is fucked up, yeah, but necessary

	if (PUBLIC == 1)
	{
		Paint.Print(15, 235, white, PUBLIC_MSG1);
		Paint.Print(15, 250, white, PUBLIC_MSG2);
		Paint.Print(15, 265, white, PUBLIC_MSG3);
	}

	if (keys[VK_INSERT] && !keysBlock[VK_INSERT])
	{
		keysBlock[VK_INSERT] = true;
		keysState[VK_INSERT] = !keysState[VK_INSERT];
	}
	if(!keys[VK_INSERT]) keysBlock[VK_INSERT] = false;

	//RIP HANG, DETECTED BY BLACKCHIPER2
	/*if (Cvar.Misc.Hung && GetAsyncKeyState(VK_LMENU) && !keysBlock[VK_LMENU])
	{
		Local.Hung = !Local.Hung;
		keysBlock[VK_LMENU] = true;
	}
	if (!GetAsyncKeyState(VK_LMENU)) keysBlock[VK_LMENU] = false;*/

	if (keysState[VK_INSERT])
		GUI.Menu();
	
	cl_entity_t* pLocal = Engine.GetLocalPlayer();

	Vector vTemp1 = pPlayerMove->origin;
	vTemp1[2] -= 8192;
	pmtrace_t* trace = Engine.PM_TraceLine(pPlayerMove->origin, vTemp1, 1, pPlayerMove->usehull, -1);

	Local.Height = abs(trace->endpos.z - pPlayerMove->origin.z);

	if (Local.Height <= 60) Local.GroundAngle = acos(trace->plane.normal[2]) / M_PI * 180;
	else Local.GroundAngle = 0;

	Local.Alive = pLocal && !(pLocal->curstate.effects & EF_NODRAW) && pLocal->player && pLocal->curstate.movetype != 6 && pLocal->curstate.movetype != 0;
	Local.Eye = pPlayerMove->origin + pPlayerMove->view_ofs;
	Local.GroundSpeed = sqrt(pPlayerMove->velocity[0] * pPlayerMove->velocity[0] + pPlayerMove->velocity[1] * pPlayerMove->velocity[1]);
	
	for (int i = 1, j = Engine.GetMaxClients(); i < j; i++)
	{
		cl_entity_s* ent = Engine.GetEntityByIndex(i);

		Player[i].ID = i;
		Player[i].Updated = Utility.IsValidEnt(ent);
		Player[i].Origin = ent->origin;
		Player[i].Visible = Utility.VisibleTrace(Local.Eye, Player[i].Origin);
		Utility.CalcFOV(Player[i].Hitbox[1] - Local.Eye, Player[i].FOV);
		
		//GHL users detection. Original idea by Hardee

	}

	if (Cvar.Visual.FullBright)
	{
		Engine.OverrideLightmap(1);
		Engine.SetLightmapColor(1.0f, 1.0f, 1.0f);
		Engine.SetLightmapDarkness(1.f);
	}
	else Engine.OverrideLightmap(0);

	if (Cvar.Visual.NoFog) Engine.pfnClientCmd(FOG_OFF); //Yes, this code and some other is executed EVERY FRAME. I'm too lazy to fix it
	else Engine.pfnClientCmd(FOG_ON);

	con_nprint_s PrintText = { 20, 0.1, 255 / 255, 255 / 255, 255 / 255 };
	if (Cvar.Misc.ShowSpeed && Local.GroundSpeed > 0.f && !Local.Hung) pEngine->Con_NXPrintf(&PrintText, SPEEDOMETER, Local.GroundSpeed);
	//PrintText.index = 19;
	//if (Local.Hung) pEngine->Con_NXPrintf(&PrintText, HUNG_MSG); 
	
	if (Cvar.Visual.CustomCrosshair) Function.DrawCrosshair();
	if (Cvar.Aim.DrawFOV) Function.DrawFOV();

	return Engine.HUD_Redraw();
}

int HUD_AddEntity()
{
	if (Cvar.Visual.NoFlash) Engine.pfnSetScreenFade(&sf);
	if (Cvar.Visual.NoSmoke) Engine.pfnHookEvent(EVENTSMOKE, smoke_event); //NoSmoke SH1T Edition, Not disabled but good-workin'

	return Engine.HUD_AddEntity();
}

int CL_CreateMove()
{
	/*if (!Local.Hung)	Utility.AdjustSpeed(1.f + (SpeedFac / 10.f));
	else				Utility.AdjustSpeed(0.f);*/

	Utility.AdjustSpeed(1.f); //This line resets the localplayer's speed, it's needed to fine working GS

	for (int i = 1, j = Engine.GetMaxClients(); i < j; i++)
	{
		if(Cvar.Aim.Enabled) Function.Aimbot(i);
	}
	
	Function.GroundStrafe();

	return Engine.CL_CreateMove();
}