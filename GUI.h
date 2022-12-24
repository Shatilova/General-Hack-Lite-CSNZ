#pragma once

#include "Misc.h"
#include "Drawing.h"
#include <ctime>

struct HGUI
{
private:
	int base = 0;
	int aimOffset = 0, oldBase = 0, chamsType = 0;
	int MousePosX, MousePosY;
	int MenuPosX, MenuPosY,
		MenuWidth, MenuHeight,
		BorderWidth = 401, BorderHeight = 25,
		MenuMinPosX = 0, MenuMinPosY = 0, MenuMaxPosX, MenuMaxPosY,
		curMousePosX, curMousePosY;
	bool Initialised = false, MousePressed, IsDragging = false, InPallete, InKeyChange = false, InListBox = false;
	enum Tabs
	{
		VISUAL,
		SETTINGS,
		AIMBOT,
		MISC
	};
	Tabs curTab;

	enum Pallets
	{
		PalNone,
		ChamsType1EN,
		ChamsType1FR,
		MenuFC,
		MenuSC,
		MenuTC,
		MenuBgC,
		MenuTxtC,
		MenuTxtC2
	};
	Pallets curPal;

	enum ListBoxes
	{
		ListNone,
		AimOffset,
		ChamsType,
	};
	ListBoxes curList;

	void Initialize();
	void Tab(int x, int y, Tabs tab);
	void CheckBox(int x, int y, bool& value, char* text);
	bool Button(int x, int y, char* text);
	void Slider(int x, int y, float min, float max, float& value, char* text, bool ThisINT, char* amout, bool extra);
	void Palette(int x, int y, Color& col, Pallets name, char* text, bool alpha);
	void SliderInPallete(int x, int y, float min, float max, int& value, char* text, bool ThisINT);
	void KeyChange(int x, int y, int& key);
	void ListBox(int x, int y, ListBoxes name, char* content[], int size, int& output);
	void DragMenu();

	void DefaultColors();
	void RandomColors();
public:
	void Menu();
};

extern HGUI GUI;