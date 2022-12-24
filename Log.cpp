/*#define _CRT_SECURE_NO_WARNINGS

#include "Log.h"

ofstream out(GENERAL_LOG);

void WriteToLog(const char* string, ...)
{
	char		strText[256];
	va_list		argumentPtr;

	va_start(argumentPtr, string);
	vsprintf(strText, string, argumentPtr);
	va_end(argumentPtr);

	out << strText << endl;
}*/