
#include <windows.h>

#include "DPEngine.h"

int WINAPI WinMain(HINSTANCE HInstance, HINSTANCE HPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	DPEngine* Engine = new DPEngine();

	if (!Engine->InitEngine(HInstance))
	{
		delete Engine;
		return 1;
	}

	Engine->Loop();

	delete Engine;
	
	return 0;
}