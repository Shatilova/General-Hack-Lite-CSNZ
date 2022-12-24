#include "Misc.h"

#define CompareMemory(Buff1, Buff2, Size) __comparemem((const UCHAR *)Buff1, (const UCHAR *)Buff2, (UINT)Size)
#define FindMemoryClone(Start, End, Clone, Size) __findmemoryclone((const ULONG)Start, (const ULONG)End, (const ULONG)Clone, (UINT)Size)
#define FindReference(Start, End, Address) __findreference((const ULONG)Start, (const ULONG)End, (const ULONG)Address)

AutoOffset offset;

typedef unsigned Cardinal;
typedef unsigned* PCardinal;
typedef unsigned** PPCardinal;

bool AutoOffset::GetStartString()
{
	if (!FindMemoryClone(HwBase, HwEnd, SCREENFADE, strlen(SCREENFADE)))
		return false;

	return true;
}

void AutoOffset::GetGameModules()
{
	/*GameUIBase = (DWORD)GetModuleHandleA("GameUI.dll");
	GameUISize = (DWORD)GetModuleSize(GameUIBase);
	GameUIEnd = GameUIBase + GameUISize - 1;

	VguiBase = (DWORD)GetModuleHandleA(VGUI);
	VguiSize = (DWORD)GetModuleSize(VguiBase);
	VguiEnd = VguiBase + VguiSize - 1;

	Vgui2Base = (DWORD)GetModuleHandleA(VGUI2);
	Vgui2Size = (DWORD)GetModuleSize(Vgui2Base);
	Vgui2End = Vgui2Base + Vgui2Size - 1;*/

	HwBase = (DWORD)GetModuleHandleA(HW_DLL);
	HwSize = (DWORD)GetModuleSize(HwBase);
	HwEnd = HwBase + HwSize - 1;

	ClientBase = (DWORD)GetModuleHandleA(CLIENT_DLL);
	ClientSize = (DWORD)GetModuleSize(ClientBase);
	ClientEnd = ClientBase + ClientSize - 1;
}

bool DataCompare(byte* pData, byte* pattern, char* mask)
{
	for (; *mask; mask++, pattern++, pData++)
	{
		if (*mask == 'x' && *pData != *pattern)
			return false;
	}
	return true;
}

DWORD FindPatternEx(DWORD dwAddress, DWORD dwLen, BYTE * bMask, char* szMask)
{
	for (DWORD i = 0; i < dwLen; i++)
		if (DataCompare((BYTE*)(dwAddress + i), bMask, szMask))
			return (DWORD)(dwAddress + i);

	return 0;
}

unsigned AutoOffset::Absolute( DWORD Addr )
{
	return Cardinal( Addr ) + *(PCardinal)(Addr)+4;
}

DWORD AutoOffset::GetModuleSize( const DWORD Address )
{
	return PIMAGE_NT_HEADERS( Address + (DWORD)PIMAGE_DOS_HEADER( Address )->e_lfanew )->OptionalHeader.SizeOfImage;
}

DWORD AutoOffset::FarProc( const DWORD Address , DWORD LB , DWORD HB )
{
	return ( ( Address < LB ) || ( Address > HB ) );
}

BOOL AutoOffset::__comparemem( const UCHAR *buff1 , const UCHAR *buff2 , UINT size )
{
	for ( UINT i = 0; i < size; i++ , buff1++ , buff2++ )
	{
		if ( ( *buff1 != *buff2 ) && ( *buff2 != 0xFF ) )
			return FALSE;
	}
	return TRUE;
}

ULONG AutoOffset::__findmemoryclone( const ULONG start , const ULONG end , const ULONG clone , UINT size )
{
	for ( ULONG ul = start; ( ul + size ) < end; ul++ )
	{
		if ( CompareMemory( ul , clone , size ) )
			return ul;
	}
	return NULL;
}

ULONG AutoOffset::__findreference( const ULONG start , const ULONG end , const ULONG address )
{
	UCHAR Pattern[5];
	Pattern[0] = 0x68;
	*(ULONG*)&Pattern[1] = address;
	return FindMemoryClone( start , end , Pattern , sizeof( Pattern ) - 1 );
}

PVOID AutoOffset::Client()
{
	DWORD Address = (DWORD)FindMemoryClone(HwBase, HwEnd, SCREENFADE, strlen(SCREENFADE));
	return (PVOID)*(PDWORD)(FindReference(HwBase, HwEnd, Address) + 0x13);
}

PVOID AutoOffset::Engine()
{
	DWORD Address = (DWORD)FindMemoryClone(HwBase, HwEnd, SCREENFADE, strlen(SCREENFADE));
	return (PVOID)* (PDWORD)(FindReference(HwBase, HwEnd, Address) + 0x0D);
}

DWORD AutoOffset::Studio()
{
	return *(PDWORD)((DWORD)pClient->HUD_GetStudioModelInterface + 0x34);
}

DWORD AutoOffset::StudioAPI()
{
	return (DWORD)pClient->HUD_GetStudioModelInterface + 0x3A;
}

DWORD AutoOffset::UserMsgBase()
{
	DWORD Address = (DWORD)FindMemoryClone(HwBase, HwEnd, USERMSGSTR, strlen(USERMSGSTR));
	return *(PDWORD)* (PDWORD)(FindReference(HwBase, HwEnd, Address) - 0x14);
}

PVOID AutoOffset::SpeedPtr()
{
	DWORD Old = NULL;
	DWORD Address = (DWORD)FindMemoryClone(HwBase, HwBase + HwSize, SPEEDSTR, strlen(SPEEDSTR));
	PVOID SpeedPtr = (PVOID)*(PDWORD)(FindReference(HwBase, HwBase + HwSize, Address) - 0x09);
	if((DWORD)SpeedPtr < 0x1000)// Just forget about it
		PVOID SpeedPtr = (PVOID)*(PDWORD)(FindReference(HwBase, HwBase + HwSize, Address) + 0x29D77B);

	VirtualProtect(SpeedPtr, sizeof(double), PAGE_READWRITE, &Old);
	return SpeedPtr;
}

DWORD AutoOffset::PlayerMove()
{
	DWORD ScreenFade = (DWORD)FindMemoryClone(HwBase, HwEnd, SCREENFADE, strlen(SCREENFADE));
	return *(DWORD*)(FindReference(HwBase, HwEnd, ScreenFade) + 0x24);
}

void AutoOffset::HookUserMsgs()
{
	pTeamInfo = HookUserMsg(TEAMINFO, TeamInfo);
}

void AutoOffset::ClientKeys()
{
	BtnBits.inDuck = *(DWORD*)(FindPatternEx(ClientBase, ClientEnd, (PBYTE)"\x8B\x35\x00\x00\x00\x00\x0F\x95\xC1\x8B\xD1\x8B\xC6\x83\xCA\x04", MASK) + 0x02);
	BtnBits.inJump = *(DWORD*)(FindPatternEx(ClientBase, ClientEnd, (PBYTE)"\x8B\x3D\x00\x00\x00\x00\x0F\x44\xD1\x8B\xCA\x8B\xC7\x83\xC9\x02", MASK) + 0x02);
}