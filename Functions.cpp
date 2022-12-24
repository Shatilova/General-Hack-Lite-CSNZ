#include "Functions.h"

bool isCaptured;
int capturedID = -1;

void Functions::Aimbot(int id)
{
	if (((Player[id].Team != Local.Team && !Cvar.Aim.FriendlyFire) || Cvar.Aim.FriendlyFire) && Player[id].Updated)
	{
		if (GetAsyncKeyState(VK_MBUTTON))
		{
			int aimTarget = -1;
			int curHitbox = -1;
			float bestFOV = 360.f;

			if (Player[id].FOV < bestFOV)
			{
				bestFOV = Player[id].FOV;
				aimTarget = id;
			}

			curHitbox = Utility.CalcBestHitbox(aimTarget);

			float oldAngles[3], newAngles[3];
			Engine.GetViewAngles(oldAngles);
			Utility.VectorAngles(Player[aimTarget].Hitbox[curHitbox] - Local.Eye, newAngles);

			if (Utility.InFOV(oldAngles, newAngles) && (capturedID == -1 || capturedID == id))
			{
				capturedID = id;
				isCaptured = true;
				Engine.SetViewAngles(newAngles);
			}
		}

		if (!GetAsyncKeyState(VK_MBUTTON) || (isCaptured && !Player[capturedID].Updated))
		{
			isCaptured = false;
			capturedID = -1;
		}
	}
}

void Functions::Bhop()//My failed attempts to make bhop. I DUNNO WHY IT ISN'T WORKIN'
{
	if (pPlayerMove->onground == 0 && GetAsyncKeyState(VK_SPACE))
	{
		*(int*)BtnBits.inJump = 4;
		*(int*)BtnBits.inJump = 5;
	}
}

void Functions::GroundStrafe()//True 101xD pasta
{
	if (Cvar.Misc.GS)
	{
		if (keys[VK_SHIFT])
		{
			static int gs_state = 0;
			if (Local.Height < 0)
			{
				if ((Local.GroundAngle < 5) && (Local.Height <= 0.000001f || pPlayerMove->onground != -1)) { Utility.AdjustSpeed(0.0001); }
				*(int*)BtnBits.inDuck = 4;
				*(int*)BtnBits.inDuck = 5;
			}
			if (gs_state == 0 && pPlayerMove->onground != -1)
			{
				if ((Local.GroundAngle < 5) && (Local.Height <= 0.000001f || pPlayerMove->onground != -1)) { Utility.AdjustSpeed(0.0001); }
				*(int*)BtnBits.inDuck = 4;
				*(int*)BtnBits.inDuck = 5;
				gs_state = 1;
			}
			else if (gs_state == 1)
			{
				if ((Local.GroundAngle < 5) && (Local.Height <= 0.000001f || pPlayerMove->onground != -1)) { Utility.AdjustSpeed(0.0001); }

				*(int*)BtnBits.inDuck = 4;
				gs_state = 0;
			}
		}
	}
	/*else if (!cvar.moving.nsdGS)
	{
		if (keys[VK_SHIFT])
		{
			if (pPlayerMove->onground == 0)
			{
				*(int*)BtnBits.inDuck = 4;
				*(int*)BtnBits.inDuck = 5;
			}
			if ((pPlayerMove->onground == 0 && pPlayerMove->bInDuck) || !(pPlayerMove->onground == 0))
				* (int*)BtnBits.inDuck = 4;
		}
	}*/
	else if (!keys[VK_SHIFT])
	{
		*(int*)BtnBits.inJump = 4;
		*(int*)BtnBits.inDuck = 4;
	}
}

void Functions::DrawFOV()
{
	Paint.FillArea(s_Screen.iWidth / 2 - (Cvar.Aim.FOV * 10), s_Screen.iHeight / 2 - (Cvar.Aim.FOV * 10), 20 * Cvar.Aim.FOV, 1, Cvar.Menu.FColor);
	Paint.FillArea(s_Screen.iWidth / 2 + (Cvar.Aim.FOV * 10), s_Screen.iHeight / 2 - (Cvar.Aim.FOV * 10), 1, 20 * Cvar.Aim.FOV, Cvar.Menu.FColor);
	Paint.FillArea(s_Screen.iWidth / 2 - (Cvar.Aim.FOV * 10), s_Screen.iHeight / 2 + (Cvar.Aim.FOV * 10), 20 * Cvar.Aim.FOV, 1, Cvar.Menu.FColor);
	Paint.FillArea(s_Screen.iWidth / 2 - (Cvar.Aim.FOV * 10), s_Screen.iHeight / 2 - (Cvar.Aim.FOV * 10), 1, 20 * Cvar.Aim.FOV, Cvar.Menu.FColor);
}

void Functions::DrawCrosshair()
{
	Color crosshairColor = Cvar.Menu.FColor;
	crosshairColor.a = 255;
	Paint.FillArea(s_Screen.iWidth / 2, s_Screen.iHeight / 2 - 30, 1, 60, crosshairColor);
	Paint.FillArea(s_Screen.iWidth / 2 - 30, s_Screen.iHeight / 2, 60, 1, crosshairColor);
}