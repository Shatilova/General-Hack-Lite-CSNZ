#include "GUI.h"

//CAUTION! BELOW TOO MUCH SH1TTY-CODE WITHOUT ANY COMMENTS. WITH CARE!

void HGUI::Initialize()
{
	if (Initialised)
		return;

	MenuMaxPosX = s_Screen.iWidth;
	MenuMaxPosY = s_Screen.iHeight;
	MenuWidth = 401;
	MenuHeight = 304;
	MenuPosX = (s_Screen.iWidth / 2) - (MenuWidth / 2);
	MenuPosY = (s_Screen.iHeight / 2) - (MenuHeight / 2);
	curTab = AIMBOT;
	curPal = PalNone;
	curList = ListNone;
	aimOffset = 0;
	InPallete = false;
	MousePressed = false;
	Initialised = true;
}

void HGUI::Tab(int x, int y, Tabs tab)
{
	int w = 100, h = 30;

	Paint.DrawLineRect(x, y, w, h, Cvar.Menu.FColor);
	Paint.FillArea(x + 3, y + 3, w - 6, h - 6, Cvar.Menu.SColor);

	if (curTab == tab)
		Paint.FillArea(x + 3, y + 3, w - 6, h - 6, Cvar.Menu.TColor);

	if (tab == VISUAL)			Paint.Print(x + 23, y + ((h + 11) / 2), Cvar.Menu.TxtColor2, MENU_TABVISUAL);
	else if (tab == SETTINGS)	Paint.Print(x + 15, y + ((h + 11) / 2), Cvar.Menu.TxtColor2, MENU_TABSETTINGS);
	else if (tab == AIMBOT)		Paint.Print(x + 18, y + ((h + 11) / 2), Cvar.Menu.TxtColor2, MENU_TABAIM);
	else if (tab == MISC)		Paint.Print(x + 28, y + ((h + 11) / 2), Cvar.Menu.TxtColor2, MENU_TABMISC);

	if (keys[VK_LBUTTON] && MousePosX >= x && MousePosX <= x + w && MousePosY >= y && MousePosY <= y + h && !MousePressed && !IsDragging && !InPallete)
	{
		if (curTab != tab) curTab = tab;
		MousePressed = true;
	}
}

void HGUI::CheckBox(int x, int y, bool& value, char* text)
{
	int w = 14, h = 14;

	Paint.DrawLineRect(x, y, w, h, Cvar.Menu.FColor);
	Paint.Print(x + 16, y + 12, Cvar.Menu.TxtColor, text);

	if (value)
		Paint.FillArea(x + 3, y + 3, w - 6, h - 6, Cvar.Menu.SColor);

	if (keys[VK_LBUTTON] && MousePosX >= x && MousePosX <= x + w && MousePosY >= y && MousePosY <= y + h && !MousePressed && !InPallete)
	{
		value = !value;
		MousePressed = true;
	}
}


bool HGUI::Button(int x, int y, char* text)
{
	int w = 150, h = 30;
	bool clicked = false;

	Paint.DrawLineRect(x, y, w, h, Cvar.Menu.FColor);
	Paint.FillArea(x + 3, y + 3, w - 5, h - 5, Cvar.Menu.SColor);
	Paint.Print(x + 10, y + 21, Cvar.Menu.TxtColor2, text);

	if (MousePosX >= x && MousePosX <= x + w && MousePosY >= y && MousePosY <= y + h && !InPallete)
	{
		Paint.FillArea(x + 3, y + 3, w - 5, h - 5, Cvar.Menu.TColor);
		Paint.Print(x + 10, y + 21, Cvar.Menu.TxtColor2, text);
	}

	if (keys[VK_LBUTTON] && MousePosX >= x && MousePosX <= x + w && MousePosY >= y && MousePosY <= y + h && !MousePressed && !InPallete)
	{
		Paint.DrawLineRect(x, y, w, h, Cvar.Menu.SColor);
		Paint.FillArea(x + 3, y + 3, w - 5, h - 5, Cvar.Menu.FColor);
		Paint.Print(x + 20, y + 21, Cvar.Menu.TxtColor2, text);

		clicked = true;
		MousePressed = true;
	}

	return clicked;
}

void HGUI::Slider(int x, int y, float min, float max, float& value, char* text, bool ThisINT, char* amout, bool extra = false)
{
	int w = 170, h = 25;

	Paint.FillArea(x, y, w, h, Cvar.Menu.SColor);
	Paint.Print(x, y - 5, Cvar.Menu.TxtColor, text);

	if (ThisINT)
		value = (int)value;

	if (value < min)
		value = min;
	else if (value > max)
		value = max;

	float one = ((w - 6) / max);
	int fullness = one * value;

	if (value < 0)
		fullness *= -1;

	Paint.FillArea(x + 3, y + 3, fullness, h - 6, Cvar.Menu.FColor);

	if (!amout)
		amout = "";

	if (ThisINT) Paint.Print(x + (w / 2) - 10, y + (h / 2) + 5, Cvar.Menu.TxtColor, SLIDER, (int)value, amout);
	else Paint.Print(x + (w / 2) - 10, y + (h / 2) + 5, Cvar.Menu.TxtColor, SLIDER2, (float)value, amout);
	
	if (MousePosX >= x + 3 && MousePosX <= x + w - 3 && MousePosY >= y + 3 && MousePosY <= y + h - 3)
	{
		if (keys[VK_LBUTTON]) {
			value = (MousePosX - x) / one;

			if (value < min)
				value = min;
			else if (value > max)
				value = max;
		}
		else if (keys[VK_RBUTTON] && min < 0) {
			value = (MousePosX - x) / one;
			value *= -1;

			if (value < min)
				value = min;
			else if (value > max)
				value = max;
		}
	}
}

void HGUI::Palette(int x, int y, Color & col, Pallets name, char* text, bool alpha)
{
	int w = 14, h = 14, w2, h2;
	if (alpha)	w2 = 190, h2 = 150;
	else		w2 = 190, h2 = 115;

	Color col2 = col;
	col2.a = 255;

	Paint.FillArea(x, y, w, h, col2);
	Paint.Print(x + 16, y + 12, Cvar.Menu.TxtColor, text);

	if (keys[VK_LBUTTON] && MousePosX >= x && MousePosX <= x + w && MousePosY >= y && MousePosY <= y + h && !MousePressed && (curPal == PalNone || curPal == name))
	{
		InPallete = !InPallete;
		curPal = name;
		MousePressed = true;
	}

	if (InPallete && curPal == name)
	{
		Paint.DrawLineRect(x, y + 14, w2, h2, Cvar.Menu.SColor);
		Paint.FillArea(x, y + 14, w2, h2, Cvar.Menu.TColor);

		SliderInPallete(x + 10, y + 24, 0, 255, col.r, SLIDER_R, true);
		SliderInPallete(x + 10, y + 59, 0, 255, col.g, SLIDER_G, true);
		SliderInPallete(x + 10, y + 94, 0, 255, col.b, SLIDER_B, true);
		if (alpha)	SliderInPallete(x + 10, y + 129, 0, 255, col.a, SLIDER_A, true);
	}
}

void HGUI::SliderInPallete(int x, int y, float min, float max, int& value, char* text, bool ThisINT)
{
	int w = 170, h = 25;

	Paint.FillArea(x, y, w, h, Cvar.Menu.SColor);

	if (ThisINT)
		value = (int)value;

	if (value < min)
		value = min;
	else if (value > max)
		value = max;

	float one = ((w - 6) / max);
	int fullness = one * value;

	if (value < 0)
		fullness *= -1;

	Paint.FillArea(x + 3, y + 3, fullness, h - 6, Cvar.Menu.FColor);

	Paint.Print(x + (w / 2) - 27, y + (h / 2) + 5, Cvar.Menu.TxtColor, SLIDERINPALLETE, text, (int)value);

	if (MousePosX >= x + 3 && MousePosX <= x + w - 3 && MousePosY >= y + 3 && MousePosY <= y + h - 3)
	{
		if (keys[VK_LBUTTON]) {
			value = (MousePosX - x) / one;

			if (value < min)
				value = min;
			else if (value > max)
				value = max;
		}
		else if (keys[VK_RBUTTON] && min < 0) {
			value = (MousePosX - x) / one;
			value *= -1;

			if (value < min)
				value = min;
			else if (value > max)
				value = max;
		}
	}
}

void HGUI::DragMenu()
{
	static int drag_x = 0;
	static int drag_y = 0;

	if (IsDragging && !keys[VK_LBUTTON])
	{
		IsDragging = false;
	}
	else if (IsDragging && keys[VK_LBUTTON])
	{
		MenuPosX = MousePosX - drag_x;
		MenuPosY = MousePosY - drag_y;
	}

	if (keys[VK_LBUTTON] && MousePosX >= MenuPosX && MousePosX <= MenuPosX + BorderWidth
		&& MousePosY >= MenuPosY && MousePosY <= MenuPosY + BorderHeight)
	{
		drag_x = MousePosX - MenuPosX;
		drag_y = MousePosY - MenuPosY;
		IsDragging = true;

		if (MenuPosX < MenuMinPosX) MenuPosX = 0;
		if (MenuPosX + MenuWidth > MenuMaxPosX) MenuPosX = MenuMaxPosX - MenuWidth;
		if (MenuPosY < MenuMinPosY) MenuPosY = 0;
		if (MenuPosY + MenuHeight > MenuMaxPosY) MenuPosY = MenuMaxPosY - MenuHeight;
	}
}

void HGUI::DefaultColors()
{
	Cvar.Menu.BgColor.r = 255;
	Cvar.Menu.BgColor.g = 255;
	Cvar.Menu.BgColor.b = 255;
	Cvar.Menu.BgColor.a = 255;

	Cvar.Menu.FColor.r = 255;
	Cvar.Menu.FColor.g = 105;
	Cvar.Menu.FColor.b = 180;
	Cvar.Menu.FColor.a = 255;

	Cvar.Menu.SColor.r = 255;
	Cvar.Menu.SColor.g = 182;
	Cvar.Menu.SColor.b = 193;
	Cvar.Menu.SColor.a = 255;

	Cvar.Menu.TColor.r = 255;
	Cvar.Menu.TColor.g = 151;
	Cvar.Menu.TColor.b = 187;
	Cvar.Menu.TColor.a = 255;

	Cvar.Menu.TxtColor.r = 0;
	Cvar.Menu.TxtColor.g = 0;
	Cvar.Menu.TxtColor.b = 0;

	Cvar.Menu.TxtColor2.r = 0;
	Cvar.Menu.TxtColor2.g = 0;
	Cvar.Menu.TxtColor2.b = 0;
}

void HGUI::RandomColors()
{
	srand(time(NULL));

	Cvar.Menu.BgColor.r = rand() % 256;
	Cvar.Menu.BgColor.g = rand() % 256;
	Cvar.Menu.BgColor.b = rand() % 256;
	Cvar.Menu.BgColor.a = rand() % 256;

	Cvar.Menu.FColor.r = rand() % 256;
	Cvar.Menu.FColor.g = rand() % 256;
	Cvar.Menu.FColor.b = rand() % 256;
	Cvar.Menu.FColor.a = rand() % 256;

	Cvar.Menu.SColor.r = rand() % 256;
	Cvar.Menu.SColor.g = rand() % 256;
	Cvar.Menu.SColor.b = rand() % 256;
	Cvar.Menu.SColor.a = rand() % 256;

	Cvar.Menu.TColor.r = rand() % 256;
	Cvar.Menu.TColor.g = rand() % 256;
	Cvar.Menu.TColor.b = rand() % 256;
	Cvar.Menu.TColor.a = rand() % 256;

	Cvar.Menu.TxtColor.r = rand() % 256;
	Cvar.Menu.TxtColor.g = rand() % 256;
	Cvar.Menu.TxtColor.b = rand() % 256;

	Cvar.Menu.TxtColor2.r = rand() % 256;
	Cvar.Menu.TxtColor2.g = rand() % 256;
	Cvar.Menu.TxtColor2.b = rand() % 256;
}

void HGUI::Menu()
{
	Initialize();
	
	Paint.FillArea(MenuPosX, MenuPosY, MenuWidth, MenuHeight, Cvar.Menu.BgColor);
	Paint.FillArea(MenuPosX, MenuPosY, MenuWidth, 25, Cvar.Menu.FColor);
	Paint.FillArea(MenuPosX, MenuPosY, 5, MenuHeight, Cvar.Menu.FColor);
	Paint.FillArea(MenuPosX, MenuPosY + MenuHeight - 5, MenuWidth, 5, Cvar.Menu.FColor);
	Paint.FillArea(MenuPosX + MenuWidth - 5, MenuPosY, 5, MenuHeight, Cvar.Menu.FColor);
	Paint.Print(MenuPosX + 20, MenuPosY + 19, Cvar.Menu.TxtColor2, HACK_TITLE);
	Tab(MenuPosX + 5, MenuPosY + 25, AIMBOT);
	Tab(MenuPosX + 102, MenuPosY + 25, VISUAL);
	Tab(MenuPosX + 199, MenuPosY + 25, MISC);
	Tab(MenuPosX + 296, MenuPosY + 25, SETTINGS);

	if (curTab == AIMBOT)
	{
		CheckBox(MenuPosX + 15, MenuPosY + 66, Cvar.Aim.Enabled, MENU_AIMENABLED);
		CheckBox(MenuPosX + 15, MenuPosY + 87, Cvar.Aim.FriendlyFire, MENU_FF);
		CheckBox(MenuPosX + 15, MenuPosY + 106, Cvar.Aim.DrawFOV, MENU_DRAWFOV);
		Slider(MenuPosX + 15, MenuPosY + 143, 0, 30, Cvar.Aim.FOV, MENU_FOV, true, "");
	}
	else if (curTab == VISUAL)
	{
		Paint.Print(MenuPosX + 70, MenuPosY + 77, Cvar.Menu.TxtColor, MENU_CHAMS);
		CheckBox(MenuPosX + 15, MenuPosY + 84, Cvar.Chams.Enabled, MENU_ENABLE);
		CheckBox(MenuPosX + 15, MenuPosY + 103, Cvar.Chams.Alpha, MENU_ALPHACHANNEL);

		Paint.Print(MenuPosX + 270, MenuPosY + 77, Cvar.Menu.TxtColor, MENU_REMOVAL);
		CheckBox(MenuPosX + 215, MenuPosY + 84, Cvar.Visual.NoInvise, MENU_INVISE);
		CheckBox(MenuPosX + 215, MenuPosY + 103, Cvar.Visual.NoGlow, MENU_GLOW);
		CheckBox(MenuPosX + 215, MenuPosY + 122, Cvar.Visual.NoSmoke, MENU_SMOKE);
		CheckBox(MenuPosX + 215, MenuPosY + 141, Cvar.Visual.NoFlash, MENU_FLASH);
		CheckBox(MenuPosX + 215, MenuPosY + 160, Cvar.Visual.NoFog, MENU_FOG);
		CheckBox(MenuPosX + 215, MenuPosY + 179, Cvar.Visual.Lambert, MENU_PSHADOWS);
		CheckBox(MenuPosX + 215, MenuPosY + 198, Cvar.Visual.FullBright, MENU_MSHADOWS);
		CheckBox(MenuPosX + 215, MenuPosY + 217, Cvar.Visual.NoCostumes, MENU_COSTUMES);

		Palette(MenuPosX + 15, MenuPosY + 122, Cvar.Chams.ENColor, ChamsType1EN, MENU_ECOLOR, Cvar.Chams.Alpha ? true : false);
		if (curPal != ChamsType1EN) Palette(MenuPosX + 15, MenuPosY + 141, Cvar.Chams.FRColor, ChamsType1FR, MENU_FCOLOR, Cvar.Chams.Alpha ? true : false);
		if (curPal != ChamsType1EN && curPal != ChamsType1FR)
		{
			Paint.Print(MenuPosX + 70, MenuPosY + 193, Cvar.Menu.TxtColor, MENU_MISC);
			CheckBox(MenuPosX + 15, MenuPosY + 200, Cvar.Visual.WallHack, MENU_WALLHACK);
			CheckBox(MenuPosX + 15, MenuPosY + 219, Cvar.Visual.CustomCrosshair, MENU_CROSSHAIR);
		}
	}
	else if (curTab == SETTINGS)
	{
		Paint.Print(MenuPosX + 50, MenuPosY + 77, Cvar.Menu.TxtColor, MENU_COLORS);
		if (Button(MenuPosX + 15, MenuPosY + 198, MENU_RANDOMCOLOR)) RandomColors();
		if (Button(MenuPosX + 15, MenuPosY + 233, MENU_DEFAULTCOLOR)) DefaultColors();
		if (Button(MenuPosX + 200, MenuPosY + 66, MENU_SAVESETTINGS)) Utility.SaveCFG();
		if (Button(MenuPosX + 200, MenuPosY + 101, MENU_LOADSETTINGS)) Utility.LoadCFG();
		Palette(MenuPosX + 15, MenuPosY + 179, Cvar.Menu.TxtColor2, MenuTxtC2, MENU_SECONDTEXT, false);
		Palette(MenuPosX + 15, MenuPosY + 160, Cvar.Menu.TxtColor, MenuTxtC, MENU_FIRSTTEXT, false);
		Palette(MenuPosX + 15, MenuPosY + 141, Cvar.Menu.BgColor, MenuBgC, MENU_BACKGROUND, true);
		Palette(MenuPosX + 15, MenuPosY + 122, Cvar.Menu.TColor, MenuTC, MENU_THIRDCOLOR, true);
		Palette(MenuPosX + 15, MenuPosY + 103, Cvar.Menu.SColor, MenuSC, MENU_SECONDCOLOR, true);
		Palette(MenuPosX + 15, MenuPosY + 84, Cvar.Menu.FColor, MenuFC, MENU_FIRSTCOLOR, true);
	}
	else if (curTab == MISC)
	{
		CheckBox(MenuPosX + 15, MenuPosY + 65, Cvar.Misc.ShowSpeed, MENU_SHOWSPEED);
		//CheckBox(MenuPosX + 15, MenuPosY + 84, Cvar.Misc.Hung, MENU_HUNG);
		CheckBox(MenuPosX + 15, MenuPosY + 84, Cvar.Misc.GS, MENU_GS);
		//Slider(MenuPosX + 215, MenuPosY + 81, 0.0, 1.0, SpeedFac, MENU_SPEEDBOOST, false, X);
	}

	Engine.GetMousePosition(&MousePosX, &MousePosY);

	DragMenu();

	if (!InPallete)	curPal = PalNone;
	if (!InListBox) curList = ListNone;
	if (!keys[VK_LBUTTON]) MousePressed = false;
}