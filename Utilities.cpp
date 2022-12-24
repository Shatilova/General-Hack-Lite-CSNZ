#include "Utilities.h"

void Utilities::CheckCFG()
{
	FILE* file = std::fopen(GHL_CFG, RPLUS);
	if (!file)
	{
		ofstream cfg(GHL_CFG);
		cfg << DEFAULT_CFG;
	}
}

void Utilities::SaveCFG()
{
	ofstream cfg(GHL_CFG);
	int cvars[120];

	cvars[0] = Cvar.Menu.BgColor.r;
	cvars[1] = Cvar.Menu.BgColor.g;
	cvars[2] = Cvar.Menu.BgColor.b;
	cvars[3] = Cvar.Menu.BgColor.a;

	cvars[4] = Cvar.Menu.FColor.r;
	cvars[5] = Cvar.Menu.FColor.g;
	cvars[6] = Cvar.Menu.FColor.b;
	cvars[7] = Cvar.Menu.FColor.a;

	cvars[8] = Cvar.Menu.SColor.r;
	cvars[9] = Cvar.Menu.SColor.g;
	cvars[10] = Cvar.Menu.SColor.b;
	cvars[11] = Cvar.Menu.SColor.a;

	cvars[12] = Cvar.Menu.TColor.r;
	cvars[13] = Cvar.Menu.TColor.g;
	cvars[14] = Cvar.Menu.TColor.b;
	cvars[15] = Cvar.Menu.TColor.a;

	cvars[16] = Cvar.Menu.TxtColor.r;
	cvars[17] = Cvar.Menu.TxtColor.g;
	cvars[18] = Cvar.Menu.TxtColor.b;

	cvars[19] = Cvar.Menu.TxtColor2.r;
	cvars[20] = Cvar.Menu.TxtColor2.g;
	cvars[21] = Cvar.Menu.TxtColor2.b;

	cvars[22] = Cvar.Aim.Enabled;
	cvars[23] = Cvar.Aim.FriendlyFire;
	cvars[24] = Cvar.Aim.FOV;

	cvars[25] = Cvar.Chams.Enabled;
	cvars[26] = Cvar.Chams.Alpha;
	cvars[27] = Cvar.Chams.ENColor.r;
	cvars[28] = Cvar.Chams.ENColor.g;
	cvars[29] = Cvar.Chams.ENColor.b;
	cvars[30] = Cvar.Chams.ENColor.a;
	cvars[31] = Cvar.Chams.FRColor.r;
	cvars[32] = Cvar.Chams.FRColor.g;
	cvars[33] = Cvar.Chams.FRColor.b;
	cvars[34] = Cvar.Chams.FRColor.a;

	cvars[35] = Cvar.Visual.NoInvise;
	cvars[36] = Cvar.Visual.NoGlow;
	cvars[37] = Cvar.Visual.NoSmoke;
	cvars[38] = Cvar.Visual.NoFlash;
	cvars[39] = Cvar.Visual.NoFog;
	cvars[40] = Cvar.Visual.Lambert;
	cvars[41] = Cvar.Visual.FullBright;
	cvars[42] = Cvar.Visual.NoCostumes;
	cvars[43] = Cvar.Visual.WallHack;
	cvars[44] = Cvar.Visual.CustomCrosshair;

	cvars[45] = Cvar.Misc.ShowSpeed;
	cvars[46] = Cvar.Misc.Hung;
	cvars[47] = Cvar.Misc.GS;
	cvars[48] = (int)(SpeedFac * 10);

	cvars[49] = Cvar.Aim.DrawFOV;

	for (int i = 0; i < 50; i++)
		cfg << cvars[i] << SPACE;
}

void Utilities::LoadCFG()
{
	CheckCFG();

	ifstream cfg(GHL_CFG);
	int buf = 0;
	int cvars[120];

	for (int i = 0; i < 50; i++)
	{
		int curInt = cfg.get();
		curInt -= 48;
		
		if (!(curInt >= 0 && curInt <= 9))
		{
			cvars[i] = buf;
			buf = 0;
			continue;
		}

		if (buf == 0) buf = curInt;
		else		  buf = buf * 10 + curInt;

		if (i >= 0) i--;
	}

	Cvar.Menu.BgColor.r = cvars[0];
	Cvar.Menu.BgColor.g = cvars[1];
	Cvar.Menu.BgColor.b = cvars[2];
	Cvar.Menu.BgColor.a = cvars[3];

	Cvar.Menu.FColor.r = cvars[4];
	Cvar.Menu.FColor.g = cvars[5];
	Cvar.Menu.FColor.b = cvars[6];
	Cvar.Menu.FColor.a = cvars[7];

	Cvar.Menu.SColor.r = cvars[8];
	Cvar.Menu.SColor.g = cvars[9];
	Cvar.Menu.SColor.b = cvars[10];
	Cvar.Menu.SColor.a = cvars[11];

	Cvar.Menu.TColor.r = cvars[12];
	Cvar.Menu.TColor.g = cvars[13];
	Cvar.Menu.TColor.b = cvars[14];
	Cvar.Menu.TColor.a = cvars[15];

	Cvar.Menu.TxtColor.r = cvars[16];
	Cvar.Menu.TxtColor.g = cvars[17];
	Cvar.Menu.TxtColor.b = cvars[18];

	Cvar.Menu.TxtColor2.r = cvars[19];
	Cvar.Menu.TxtColor2.g = cvars[20];
	Cvar.Menu.TxtColor2.b = cvars[21];

	Cvar.Aim.Enabled = cvars[22];
	Cvar.Aim.FriendlyFire = cvars[23];
	Cvar.Aim.FOV = cvars[24];

	Cvar.Chams.Enabled = cvars[25];
	Cvar.Chams.Alpha = cvars[26];
	Cvar.Chams.ENColor.r = cvars[27];
	Cvar.Chams.ENColor.g = cvars[28];
	Cvar.Chams.ENColor.b = cvars[29];
	Cvar.Chams.ENColor.a = cvars[30];
	Cvar.Chams.FRColor.r = cvars[31];
	Cvar.Chams.FRColor.g = cvars[32];
	Cvar.Chams.FRColor.b = cvars[33];
	Cvar.Chams.FRColor.a = cvars[34];

	Cvar.Visual.NoInvise = cvars[35];
	Cvar.Visual.NoGlow = cvars[36];
	Cvar.Visual.NoSmoke = cvars[37];
	Cvar.Visual.NoFlash = cvars[38];
	Cvar.Visual.NoFog = cvars[39];
	Cvar.Visual.Lambert = cvars[40];
	Cvar.Visual.FullBright = cvars[41];
	Cvar.Visual.NoCostumes = cvars[42];
	Cvar.Visual.WallHack = cvars[43];
	Cvar.Visual.CustomCrosshair = cvars[44];

	Cvar.Misc.ShowSpeed = cvars[45];
	Cvar.Misc.Hung = cvars[46];
	Cvar.Misc.GS = cvars[47];
	Cvar.Misc.SpeedFac = cvars[48];

	Cvar.Aim.DrawFOV = cvars[49];

	SpeedFac = (float)Cvar.Misc.SpeedFac / 10.f;
}

int Utilities::CalcBestHitbox(int target)//It's now to be reformulated
{
	float bestHeight, bestDist = 0.f;
	int highestHitboxes[2] = { -1, -1 }, result;

	if (target == -1)
		return 0;

	bestHeight = Engine.GetEntityByIndex(target)->origin.z;

	for (int a = 1; a < 12; a++)
	{
		if (Player[target].Hitbox[a].z > bestHeight)
		{
			highestHitboxes[1] = highestHitboxes[0];
			highestHitboxes[0] = a;
			bestHeight = Player[target].Hitbox[a].z;
		}
	}

	if (highestHitboxes[0] == -1) return 0;

	for (int i = 0; i < 2; i++)
	{
		if (highestHitboxes[i] == -1)
			continue;

		float x = Player[target].Origin.x - Player[target].Hitbox[highestHitboxes[i]].x;
		float y = Player[target].Origin.y - Player[target].Hitbox[highestHitboxes[i]].y;
		float dist = sqrt(pow(x, 2) + pow(y, 2));
		if (bestDist == 0.f) bestDist = dist;

		if (dist <= bestDist)
		{
			bestDist = dist;
			result = highestHitboxes[i];
		}
	}
		//Engine.Con_Printf("ID - %i, Hitbox - %i, Coord - %1.0f, %1.0f, %1.0f\n", target, result, Player[target].Hitbox[result].x, Player[target].Hitbox[result].y, Player[target].Hitbox[result].z);
	return result;
}

bool Utilities::IsValidEnt(cl_entity_s* ent)
{
	if ((ent->index != Local.ID) && !(ent->curstate.effects & EF_NODRAW) && ent->player && (ent->model->name != 0 || ent->model->name != "") && !(ent->curstate.messagenum < Engine.GetLocalPlayer()->curstate.messagenum) && ent->curstate.movetype != 6 && ent->curstate.movetype != 0)
		return true;
	else
		return false;
}

void Utilities::CalcFOV(Vector origin, float FOV)
{
	float oldAngles[3], newAngles[3];
	Vector result;

	Engine.GetViewAngles(oldAngles);
	VectorAngles(origin, newAngles);
	VectorSubtract(oldAngles, newAngles, result);
	FOV = result.Length2D();
}

bool Utilities::InFOV(float* oldAngles, float* newAngles)
{
	float minX = oldAngles[0] - Cvar.Aim.FOV,
		maxX = oldAngles[0] + Cvar.Aim.FOV,
		minY = oldAngles[1] - Cvar.Aim.FOV,
		maxY = oldAngles[1] + Cvar.Aim.FOV;

	if (minY < 0.f) minY += 360.f;
	if (maxY > 360.f) maxY -= 360.f;

	return (newAngles[0] >= minX
		&& newAngles[0] <= maxX
		&& newAngles[1] >= minY
		&& newAngles[1] <= maxY);
}

void Utilities::VectorAngles(const float* forward, float* angles)
{
	float tmp, yaw, pitch;

	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		if (forward[2] > 0)
			pitch = 270;
		else
			pitch = 90;
	}
	else
	{
		yaw = (atan2(forward[1], forward[0]) * 180 / M_PI);
		if (yaw < 0)
			yaw += 360;

		tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = (atan2(-forward[2], tmp) * 180 / M_PI);
		if (pitch < 0)
			pitch += 360;
	}

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;

	while (angles[0] < -89) { angles[0] += 180; angles[1] += 180; }
	while (angles[0] > 89) { angles[0] -= 180; angles[1] += 180; }
	while (angles[1] < 0) { angles[1] += 360; }
	while (angles[1] > 360) { angles[1] -= 360; }
}

int Utilities::ColorDarkening(int col, int x)
{
	int color = col - x;
	if (color < 0) color = 0;
	return color;
}

bool Utilities::Compare(char* str, std::string type[], int size)//Sorry for that
{
	if (size == 1)
	{
		const char* str2 = type[0].c_str();
		if (strstr(str, str2))
			return 1;
	}
	else
	{
		for (int i = 0; i < size - 1; i++)
		{
			const char* str2 = type[i].c_str();
			if (strstr(str, str2))
				return 1;
		}
	}

	return 0;
}

bool Utilities::VisibleTrace(float* pflFrom, float* pflTo)
{
	if (!pflFrom || !pflTo) { return false; }
	pmtrace_t pTrace;
	Engine.pEventAPI->EV_SetTraceHull(2);
	Engine.pEventAPI->EV_PlayerTrace(pflFrom, pflTo, PM_GLASS_IGNORE | PM_STUDIO_BOX, Local.ID, &pTrace);
	return (pTrace.fraction == 1.0f);
}

void Utilities::AdjustSpeed(double x)
{
	if (dwSpeedPtr == 0)
		dwSpeedPtr = pSpeed;

	static double LastSpeed = 1;
	if (x != LastSpeed)
	{
		*(double*)dwSpeedPtr = (x * 1000);
		LastSpeed = x;
	}
}