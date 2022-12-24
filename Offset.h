#pragma once

class AutoOffset
{
private:
	DWORD GameUIBase, GameUISize, GameUIEnd;
	DWORD VguiBase, VguiSize, VguiEnd;
	DWORD Vgui2Base, Vgui2Size, Vgui2End;
	DWORD HwBase, HwSize, HwEnd;
	DWORD ClientBase, ClientSize, ClientEnd;

	BOOL __comparemem( const UCHAR *buff1 , const UCHAR *buff2 , UINT size );
	ULONG __findmemoryclone( const ULONG start , const ULONG end , const ULONG clone , UINT size );
	ULONG __findreference( const ULONG start , const ULONG end , const ULONG address );

	DWORD FarProc( const DWORD Address , DWORD LB , DWORD HB );

public:
	BYTE HLType;

	bool GetStartString();
	void GetGameModules();

	PVOID Client();
	PVOID Engine();
	DWORD Studio();
	DWORD StudioAPI();

	unsigned Absolute( DWORD Addr );
	DWORD GetModuleSize( const DWORD Address );

	PVOID ClientFuncs();
	PVOID EngineFuncs();
	PVOID StudioFuncs();
	DWORD UserMsgBase();
	PVOID SpeedPtr();
	DWORD PlayerMove();

	void HookUserMsgs();
	void ClientKeys();
};

extern AutoOffset offset;