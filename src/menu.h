#pragma once
#include "constants.h"

namespace Menu {
	void toggleMenu();
	void init();
	void startRender();
	void render();
	void endRender();
	BOOL __stdcall newSwapBuffers(HDC hdc);
}