#include "pch.h"
#include "Platform.h"
#include <string>
#include <vector>
#include <codecvt>

#if _WIN32
#include <Windows.h>

struct thread_data {
	void(*func)();
	thread_data(void(*f)()) : func(f) {}
};

DWORD WINAPI thread_func(LPVOID lpParameter) {
	thread_data *td = (thread_data*)lpParameter;
	td->func();
	delete td;
	return 0;
}

// Creates a thread calling `void f()`
void spawnThread(void(*f)()) {
	CreateThread(NULL, 0, thread_func, new thread_data(f), 0, 0);
}

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
#error Incompatible Platform
#endif
