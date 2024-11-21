#pragma once

#include <Windows.h>
#include "genCode.h"

extern HMODULE hModule;
extern uintptr_t exeBaseAddress;

extern Player* localPlayerPtr;
extern EntityList* players;
extern int numPlayers;

void resetPointers();

typedef BOOL(__stdcall* _wglSwapBuffers)(HDC hdc);
extern _wglSwapBuffers originalSwapBuffers;

typedef int(__fastcall* _SDL_SetRelativeMouseMode)(int node);
extern _SDL_SetRelativeMouseMode originalSetRelativeMouseMode;