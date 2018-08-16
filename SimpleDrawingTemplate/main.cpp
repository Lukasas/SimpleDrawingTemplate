#include <Windows.h>
#include "PaintClass.h"
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

BasePaint *cBasePaint;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(wc);
	wc.cbWndExtra = 0;
	wc.hbrBackground = 0;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "SimpleDrawingTemplate";
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wc);

	HWND hWnd = CreateWindowEx(0, "SimpleDrawingTemplate", "SimpleDrawingTemplate", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, HWND_DESKTOP, 0, hInstance, NULL);

	cBasePaint = new PaintClass(hWnd);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
		}
		else
		{
			cBasePaint->Paint();
			Sleep(16);
		}
	delete cBasePaint;
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		break;
	//case WM_EXITSIZEMOVE:
	case WM_WINDOWPOSCHANGED:
		cBasePaint->RecalculateWindowSizes();
		break;
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_LBUTTONDOWN:
		cBasePaint->SendMousePressEvent((MouseButton)message, MouseDown, Position(LOWORD(lParam), HIWORD(lParam)));
		break;
	case WM_MBUTTONUP:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		cBasePaint->SendMousePressEvent((MouseButton)(message - 1), MouseUp, Position(LOWORD(lParam), HIWORD(lParam)));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ERASEBKGND:
		return false;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}