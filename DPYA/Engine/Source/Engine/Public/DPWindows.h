#pragma once

#include <windows.h>

class DPWindows
{
public:
	DPWindows(const DPWindows&) = delete;
	DPWindows& operator=(const DPWindows&) = delete;

	~DPWindows() { Instance = nullptr; }

	bool InitWindows(HINSTANCE HInstance);
	bool Tick();

	static DPWindows* Get();
	const HWND& GetHWNND() const { return HWnd; }

private:
	DPWindows() { }

	static LRESULT CALLBACK WindowProc(HWND InHWnd, UINT Message, WPARAM WParam, LPARAM LParam);
	LRESULT ProcessMessage(HWND InHWnd, UINT Message, WPARAM WParam, LPARAM LParam);

private:
	static DPWindows* Instance;

	HWND HWnd;
};