#include "Render.h"

int StudioDrawPlayer(int flags, struct entity_state_s* pplayer)
{
	if (Cvar.Visual.WallHack && Local.Alive)//You could remove the second condition, but then other players will be flashing when you a spectator
		glClear(GL_ACCUM); //WH from 2006 lmao
	
	return StudioAPI.StudioDrawPlayer(flags, pplayer);
}

int StudioDrawModel(int flags)
{
	cl_entity_s* ent = Studio.GetCurrentEntity();
	if (Cvar.Visual.NoCostumes && strstr(ent->model->name, COSTUME))//There are some problems about NoCostumes, but i don't rememba what exactly
		return 0;

	int oldR, oldG, oldB;
	Color FRColorWall, ENColorWall;

	for (int i = 1; i < 33; i++)
	{
		cl_entity_s* ent = Engine.GetEntityByIndex(i);
		cl_entity_s* localEnt = Engine.GetViewModel();

		if (ent->player)
		{
			FRColorWall.r = Utility.ColorDarkening(Cvar.Chams.FRColor.r, 75);
			FRColorWall.g = Utility.ColorDarkening(Cvar.Chams.FRColor.g, 75);
			FRColorWall.b = Utility.ColorDarkening(Cvar.Chams.FRColor.b, 75);

			ENColorWall.r = Utility.ColorDarkening(Cvar.Chams.ENColor.r, 75);
			ENColorWall.g = Utility.ColorDarkening(Cvar.Chams.ENColor.g, 75);
			ENColorWall.b = Utility.ColorDarkening(Cvar.Chams.ENColor.b, 75);

			if (!Cvar.Chams.Enabled && Cvar.Visual.NoInvise)
			{
				//if (Utility.Compare(ent->model->name, ZM_LIGHT, std::size(ZM_LIGHT)) || strstr(ent->model->name, JOKER))
				//{
					ent->curstate.rendermode = 1;
					ent->curstate.renderamt = 200;
				//}
				if (Cvar.Visual.NoGlow) ent->curstate.renderfx = 0;
			}
			else if (!Cvar.Chams.Enabled && !Cvar.Visual.NoInvise && Cvar.Visual.NoGlow)
			{
				ent->curstate.renderfx = 0;
				ent->curstate.renderamt = 200;
			}

			if (!Cvar.Chams.Enabled && ent->index != localEnt->index)
			{
				ent->curstate.rendermode = 1;
				ent->curstate.renderamt = 255;
			}

			if (Cvar.Chams.Enabled || (Cvar.Chams.Enabled && Cvar.Visual.NoInvise) || (Cvar.Chams.Enabled && Cvar.Visual.NoInvise))
			{
				if (!Cvar.Chams.Alpha)
				{
					ent->curstate.renderfx = 22;
					ent->curstate.rendermode = 5;
					ent->curstate.renderamt = 50;
				}
				else
				{
					ent->curstate.renderfx = 22;
					ent->curstate.rendermode = 4;
				}

				if (Player[i].Team == Local.Team && Player[i].Visible)
				{
					ent->curstate.rendercolor.r = Cvar.Chams.FRColor.r;
					ent->curstate.rendercolor.g = Cvar.Chams.FRColor.g;
					ent->curstate.rendercolor.b = Cvar.Chams.FRColor.b;
					if (Cvar.Chams.Alpha) ent->curstate.renderamt = Cvar.Chams.FRColor.a;
				}
				else if (Player[i].Team == Local.Team && !Player[i].Visible)
				{
					ent->curstate.rendercolor.r = FRColorWall.r;
					ent->curstate.rendercolor.g = FRColorWall.g;
					ent->curstate.rendercolor.b = FRColorWall.b;
					if(Cvar.Chams.Alpha) ent->curstate.renderamt = Cvar.Chams.FRColor.a;
				}
				else if (Player[i].Team != Local.Team && Player[i].Visible)
				{
					ent->curstate.rendercolor.r = Cvar.Chams.ENColor.r;
					ent->curstate.rendercolor.g = Cvar.Chams.ENColor.g;
					ent->curstate.rendercolor.b = Cvar.Chams.ENColor.b;
					if (Cvar.Chams.Alpha) ent->curstate.renderamt = Cvar.Chams.ENColor.a;
				}
				else if (Player[i].Team != Local.Team && !Player[i].Visible)
				{
					ent->curstate.rendercolor.r = ENColorWall.r;
					ent->curstate.rendercolor.g = ENColorWall.g;
					ent->curstate.rendercolor.b = ENColorWall.b;
					if (Cvar.Chams.Alpha) ent->curstate.renderamt = Cvar.Chams.ENColor.a;
				}
			}
		}

		if (ent->index == localEnt->index)
			ent->curstate.renderamt = 255;
	}

	cl_entity_s* ent2 = Studio.GetCurrentEntity();

	if (!ent2->player) ent2->curstate.rendermode = 0;

	return StudioAPI.StudioDrawModel(flags);
}

void StudioSetupLighting(struct alight_s* plighting)
{
	cl_entity_s* ent = Studio.GetCurrentEntity();

	if (ent->player && Cvar.Visual.Lambert)
		plighting->ambientlight = 192;

	return Studio.StudioSetupLighting(plighting);
}

void StudioEntityLight(struct alight_s* plight)
{
	cl_entity_s* ent = Studio.GetCurrentEntity();

	if (ent && ent->player && ent->index != -1 && ent->index != Local.ID && Utility.IsValidEnt(ent))
	{
		for (int i = 1; i <= 11; ++i)
		{
			Vector vBBMin, vBBMax, vVel;

			typedef float BoneMatrix_t[MAXSTUDIOBONES][3][4];

			model_t* pModel;
			studiohdr_t* pStudioHeader;
			BoneMatrix_t* pBoneMatrix;
			mstudiobbox_t* pHitbox;

			pModel = Studio.SetupPlayerModel(ent->index);
			pStudioHeader = (studiohdr_t*)Studio.Mod_Extradata(pModel);
			pBoneMatrix = (BoneMatrix_t*)Studio.StudioGetBoneTransform();
			pHitbox = (mstudiobbox_t*)((byte*)pStudioHeader + pStudioHeader->hitboxindex);

			VectorTransform(pHitbox[i].bbmin, (*pBoneMatrix)[pHitbox[i].bone], vBBMin);
			VectorTransform(pHitbox[i].bbmax, (*pBoneMatrix)[pHitbox[i].bone], vBBMax);

			Player[ent->index].Hitbox[i] = (vBBMax + vBBMin) * 0.5f;
		}
	}

	return Studio.StudioEntityLight(plight);
}