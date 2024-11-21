#include "iostream"
#include "Windows.h"
#include "constants.h"
#include "genCode.h"
#include "esp.h"
#include "detours/detours.h"
#include "menu.h"

void aimbot() {
    while (true) {
        resetPointers();
        ESP::aimboit();
        Sleep(50);
        if (GetAsyncKeyState(VK_DELETE))
            Menu::toggleMenu();
    }
}
void hook() {
    Sleep(1000);
    DisableThreadLibraryCalls(hModule);
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)originalSwapBuffers, Menu::newSwapBuffers);
    DetourTransactionCommit();
}

void console() {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONIN$", "r", stdin);
    std::cout << "Console created" << std::endl;
    while (true) {
        std::string input;
        std::cin >> input;
        if (input == "exit")
            break;
        if (input == "up")
            localPlayerPtr->position.y += 5;
        if (input == "down")
            localPlayerPtr->position.y -= 5;
        if (input == "print")
            std::cout << "Local player Ptr: " << localPlayerPtr << std::endl;
        if (input == "amount")
            std::cout << "Number of players " << numPlayers << std::endl;
        if (input == "ent") {
            for (int i = 1; i < numPlayers; i++) {
                if (players->players[i] == nullptr || players->players[i]->vtable == nullptr)
                    break;
                std::cout << "Entity " << i << "Pos " << players->players[i]->position.x << " " << players->players[i]->position.y << " " << players->players[i]->position.z << std::endl;
            }
        }
    }
    FreeConsole();
}

// Funcao principal
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    // Se a DLL for atribuida ao processo, ela cria 3 threads com as funcoes abaixo
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)console, nullptr, 0, nullptr);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)hook, nullptr, 0, nullptr);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)aimbot, nullptr, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

