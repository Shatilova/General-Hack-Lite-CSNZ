#pragma once

#include <Windows.h>
#include "Misc.h"

struct Drawing
{
private:
	short	cheight;
	short	cwidth[255];
	char   name[20];
	int   height;
	int   width;
	UINT   g_FontListID;
	HDC hDC;
	HFONT hFont;
	HFONT hOldFont;

	void Render(int x, int y, int r, int g, int b, char* string);
public:
	void InitText();
	void Print(int x, int y, Color col, char* string, ...);
	void DrawCircle(float position[2], float points, float radius, int r, int g, int b, int a);
	void DrawLineRect(int x, int y, int h, int w, Color col);
	void FillArea(int x, int y, int w, int h, Color col);
	void Box(int x, int y, int w, int h, int lw, Color col);
};

extern Drawing Paint;