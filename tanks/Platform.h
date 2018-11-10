#pragma once

void spawnThread(void(*f)());
void createDevConsole();
void destroyDevConsole();
void outputString(const char* string, char* format);