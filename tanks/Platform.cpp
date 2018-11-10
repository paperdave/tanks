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
	return 0;
}

void spawnThread(void(*f)()) {
	CreateThread(NULL, 0, thread_func, new thread_data(f), 0, 0);
}

void createDevConsole() {
	AllocConsole();
	SetConsoleTitle(L"Dave's Tanks");
	//EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_GRAYED);
	//DrawMenuBar(GetConsoleWindow());
}

void destroyDevConsole() {
	FreeConsole();
}

std::string vformat(const char *fmt, va_list ap)
{
	// Allocate a buffer on the stack that's big enough for us almost
	// all the time.  Be prepared to allocate dynamically if it doesn't fit.
	size_t size = 1024;
	char stackbuf[1024];
	std::vector<char> dynamicbuf;
	char *buf = &stackbuf[0];
	va_list ap_copy;

	while (1) {
		// Try to vsnprintf into our buffer.
		va_copy(ap_copy, ap);
		int needed = vsnprintf(buf, size, fmt, ap);
		va_end(ap_copy);

		// NB. C99 (which modern Linux and OS X follow) says vsnprintf
		// failure returns the length it would have needed.  But older
		// glibc and current Windows return -1 for failure, i.e., not
		// telling us how much was needed.

		if (needed <= (int)size && needed >= 0) {
			// It fit fine so we're done.
			return std::string(buf, (size_t)needed);
		}

		// vsnprintf reported that it wanted to write more characters
		// than we allotted.  So try again using a dynamic buffer.  This
		// doesn't happen very often if we chose our initial size well.
		size = (needed > 0) ? (needed + 1) : (size * 2);
		dynamicbuf.resize(size);
		buf = &dynamicbuf[0];
	}
}

void outputString(const char* string, va_list format) {
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring out = converter.from_bytes(vformat(string, format));
	
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), out.c_str(), (DWORD)out.length(), nullptr, nullptr);
}

#else
#error Incompatible Platform
#endif
