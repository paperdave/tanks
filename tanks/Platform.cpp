#include "pch.h"
#include "Platform.h"
#include <string>
#include <vector>
#include <codecvt>

#include <thread>

void spawnThread(void(*f)()) {
	std::thread thread(f);
	thread.detach();
}

#if _WIN32
#include <windows.h>

// Creates a pop up console window.
void createDevConsole() {
	AllocConsole();
	SetConsoleTitle(L"Dave's Tanks");
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);
	
	// EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_GRAYED);
	// DrawMenuBar(GetConsoleWindow());
}

void destroyDevConsole() {
	FreeConsole();
}

#else

// Creates a pop up console window. Not implemented for linux
void createDevConsole() {
}

void destroyDevConsole() {
}

#endif

