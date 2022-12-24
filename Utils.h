#pragma once

#include "Misc.h"

pfnUserMsgHook HookUserMsg( char *szMsgName , pfnUserMsgHook pfn );

PVOID CaptureInterface(CreateInterfaceFn Interface, char* InterfaceName);
CreateInterfaceFn CaptureFactory(char* FactoryModule);