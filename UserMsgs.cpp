#include "Misc.h"

pfnUserMsgHook pTeamInfo;

int TeamInfo(const char* pszName, int iSize, void* pbuf)
{
	BEGIN_READ(pbuf, iSize);

	cl_entity_s* Entity = Engine.GetLocalPlayer();

	int Index = READ_BYTE();
	char* Team = READ_STRING();

	cl_entity_s* localPlayer = pEngine->GetLocalPlayer();
	Local.ID = localPlayer->index;

	if (!lstrcmpiA(Team, C))
	{
		if (Index == Local.ID) Local.Team = 1;
		else				   Player[Index].Team = 1;
	}
	else if (!lstrcmpiA(Team, T))
	{
		if (Index == Local.ID) Local.Team = 2;
		else				   Player[Index].Team = 2;
	}
	else
		Player[Index].Team = 0;

	return pTeamInfo(pszName, iSize, pbuf);
}