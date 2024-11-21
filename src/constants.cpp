#include "constants.h"

// O tipo HMODULE basicamente pode ser qualquer modulo na memoria.
// GetModuleHandle recupera um modulo que esta rodando na memoria
HMODULE hModule = GetModuleHandle(nullptr);
uintptr_t exeBaseAddress = (uintptr_t)GetModuleHandle(nullptr);

// *(Player**) eh um cast para (Player**) referenciar um ponteiro duplo, e *(Player**) desreferenciar esse ponteiro.
extern Player* localPlayerPtr = *(Player**)(exeBaseAddress + 0x17E0A8);

uintptr_t playersAddr = exeBaseAddress + 0x18AC04;
extern EntityList* players = (EntityList*)playersAddr;

extern int numPlayers = *(int*)(exeBaseAddress + 0x191FD4);

void resetPointers(){
	localPlayerPtr = *(Player**)(exeBaseAddress + 0x17E0A8);
	players = *(EntityList**)(playersAddr);
	numPlayers = *(int*)(exeBaseAddress + 0x191FD4);
}

_wglSwapBuffers originalSwapBuffers = (_wglSwapBuffers)GetProcAddress(GetModuleHandle(L"OPENGL32.dll"), "wglSwapBuffers");

_SDL_SetRelativeMouseMode originalSetRelativeMouseMode = (_SDL_SetRelativeMouseMode)(GetProcAddress(GetModuleHandle(L"SDL2.dll"), "SDL_SetRelativeMouseMode"));
