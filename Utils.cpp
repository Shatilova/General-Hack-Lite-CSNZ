#include "Misc.h"

PUserMsg UserMsgByName( char* szMsgName )
{
	PUserMsg Ptr = nullptr;
	Ptr = pUserMsgBase;
	while ( Ptr->next )
	{
		if ( !strcmp( Ptr->name , szMsgName ) )
			return Ptr;
		Ptr = Ptr->next;
	}
	Ptr->pfn = 0;
	return Ptr;
}

pfnUserMsgHook HookUserMsg( char *szMsgName , pfnUserMsgHook pfn )
{
	PUserMsg Ptr = nullptr;
	pfnUserMsgHook Original = nullptr;
	Ptr = UserMsgByName( szMsgName );
	if ( Ptr->pfn != 0 ) {
		Original = Ptr->pfn;
		Ptr->pfn = pfn;
		return Original;
	}

	return Original;
}

PVOID CaptureInterface(CreateInterfaceFn Interface, char* InterfaceName)
{
	PVOID dwPointer = nullptr;

	dwPointer = (PVOID)(Interface(InterfaceName, 0));

	return dwPointer;
}

CreateInterfaceFn CaptureFactory(char* FactoryModule)
{
	CreateInterfaceFn Interface = 0;

	HMODULE hFactoryModule = GetModuleHandleA(FactoryModule);

	if (hFactoryModule)
		Interface = (CreateInterfaceFn)(GetProcAddress(hFactoryModule, CREATEINTERFACE));

	return Interface;
}