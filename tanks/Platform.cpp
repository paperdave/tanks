#include "pch.h"
#include "Platform.h"

#if _WIN32
#include <Windows.h>

struct thread_data
{
	void(*func)();
	thread_data(void(*f)()) : func(f) {}
};

DWORD WINAPI thread_func(LPVOID lpParameter) {
	thread_data *td = (thread_data*)lpParameter;
	td->func();
	return 0;
}

void spawnThread(void(*f)()) {
	CreateThread(NULL, 0, thread_func, new thread_data(f), 0, 0);
}

#else
#error Incompatible Platform
#endif
