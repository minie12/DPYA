// include the basic windows header file

#include "DPWindows.h"

DPWindows* DPWindows::Instance = nullptr;

static const unsigned int SCREENWIDTH = 600;
static const unsigned int SCREENHEIGHT = 800;

DPWindows* DPWindows::Get()
{
	if (nullptr == Instance)
	{
		Instance = new DPWindows();
	}

	return Instance;
}

LRESULT CALLBACK DPWindows::WindowProc(HWND InHWnd, UINT Message, WPARAM WParam, LPARAM LParam)
{
	return Instance->ProcessMessage(InHWnd, Message, WParam, LParam);
}

LRESULT DPWindows::ProcessMessage(HWND InHWnd, UINT Message, WPARAM WParam, LPARAM LParam)
{
	switch (Message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONUP:
	case WM_LBUTTONDOWN:
	case WM_KEYDOWN:
	case WM_KEYUP:
	return LRESULT();

	break;
	}

	return DefWindowProc(InHWnd, Message, WParam, LParam);
}

// the entry point for any Windows program
bool DPWindows::InitWindows(HINSTANCE HInstance)
{
	// this struct holds information for the window class
	WNDCLASSEX wc;

	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = &WindowProc;
	wc.hInstance = HInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"DPYA_GAME";

	// register the window class
	RegisterClassEx(&wc);

	// create the window and use the result as the handle
	HWnd = CreateWindowEx(NULL,
		L"DPYA_GAME",    // name of the window class
		L"DPYA_GAME",    // title of the window
		WS_OVERLAPPED | WS_SYSMENU,    // window style
		CW_USEDEFAULT,    // x-position of the window
		CW_USEDEFAULT,    // y-position of the window
		SCREENWIDTH,    // width of the window
		SCREENHEIGHT,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		HInstance,    // application handle
		NULL);    // used with multiple windows, NULL

	// display the window on the screen
	ShowWindow(HWnd, SW_SHOW);

	return true;
}

bool DPWindows::Tick()
{
	// enter the main loop:
	MSG msg = { 0 };

	// Check to see if any messages are waiting in the queue
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		// translate keystroke messages into the right format
		TranslateMessage(&msg);

		// send the message to the WindowProc function
		DispatchMessage(&msg);

		// check to see if it's time to quit
		if (msg.message == WM_QUIT)
			return false;
	}
	
	return true;
}