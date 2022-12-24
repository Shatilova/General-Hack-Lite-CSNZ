#define _CRT_SECURE_NO_WARNINGS

#include "Drawing.h"

void Drawing::InitText()//also pasta
{
	hDC = wglGetCurrentDC();
	g_FontListID = glGenLists(256);

	hFont = CreateFontA(18, 9, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
		OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, GEORGIA);

	hOldFont = (HFONT)SelectObject(hDC, hFont);

	wglUseFontBitmapsA(hDC, 0, 255, g_FontListID);
	for (int i = 0; i < 255; i++)
	{
		SIZE s;
		char line[2] = { (char)i, 0 };
		GetTextExtentPointA(hDC, line, 1, &s);
		cwidth[i] = s.cx;
		cheight = s.cy;
	}
	SelectObject(hDC, hOldFont);
	DeleteObject(hFont);
}

void Drawing::Render(int x, int y, int r, int g, int b, char* string)
{
	int i = 0;
	while (x < 0)
	{
		x += cwidth[string[i]];
		i++; if (!string[i]) { return; }
	}

	glColor4ub(r, g, b, 255);
	glRasterPos2i(x, y);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glPushAttrib(GL_LIST_BIT);
	glListBase(g_FontListID);
	glCallLists(strlen(string) - i, GL_UNSIGNED_BYTE, string + i);
	glPopAttrib();
}

void Drawing::Print(int x, int y, Color col, char* string, ...)
{
	glDisable(GL_TEXTURE_2D);

	char		strText[256];
	va_list		argumentPtr;

	va_start(argumentPtr, string);
	vsprintf(strText, string, argumentPtr);
	va_end(argumentPtr);

	int drawlen = 0;
	for (char* p = strText; *p; p++) { drawlen += cwidth[*p]; }

	Render(x, y, col.r, col.g, col.b, strText);

	glEnable(GL_TEXTURE_2D);
}

void Drawing::FillArea(int x, int y, int w, int h, Color col)
{
	pEngine->pfnTintRGBA(x, y, w, h, col.r, col.g, col.b, col.a);
}

void Drawing::DrawLineRect(int x, int y, int w, int h, Color col)
{
	Box(x, y, w, h, 3, col);
}

void Drawing::Box(int x, int y, int w, int h, int lw, Color col)
{
	FillArea(x, y, w, lw, col);
	FillArea(x + w - lw, y + lw, lw, h - lw, col);
	FillArea(x, y + lw, lw, h - lw, col);
	FillArea(x + lw, y + h - lw, w - lw * 2, lw, col);
}