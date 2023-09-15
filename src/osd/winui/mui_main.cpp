// For licensing and usage information, read docs/release/winui_license.txt
//****************************************************************************
#ifndef WINUI
#define WINUI
#endif

// import the main() from MAME, but rename it so we can call it indirectly
#undef main
#undef wmain
#define main mame_main
#define wmain mame_main
#include "main.cpp"
#undef main
#undef wmain

#include "winui.h"

void wchar2strstring(std::string& szDst, WCHAR* wchart)
{
	wchar_t* wtext = wchart;
	DWORD dwNmu = WideCharToMultiByte(CP_OEMCP, NULL, wtext, -1, NULL, 0, NULL, FALSE);
	char* psTest;
	psTest = new char[dwNmu];
	WideCharToMultiByte(CP_OEMCP, NULL, wtext, -1, psTest, dwNmu, NULL, FALSE);
	szDst = psTest;
	delete[]psTest;
}

wchar_t* trstring2wchar(const  char* str)
{
	int mystringsize = (int)(strlen(str) + 1);
	WCHAR* wchart = new wchar_t[mystringsize];
	MultiByteToWideChar(CP_ACP, 0, str, -1, wchart, mystringsize);
	return wchart;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	auto wr = trstring2wchar(lpCmdLine);
	int ret =  MameUIMain(hInstance, wr, nCmdShow);
	delete[] wr;
	return ret;
}

