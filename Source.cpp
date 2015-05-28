#define UNICODE
#pragma comment(lib,"imm32")
#include<windows.h>

TCHAR szClassName[] = TEXT("Window");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit;
	static HWND hButton1;
	static HWND hButton2;
	switch (msg)
	{
	case WM_CREATE:
		hEdit = CreateWindow(TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE, 10, 10, 256, 32, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		hButton1 = CreateWindow(TEXT("BUTTON"), TEXT("‚©‚È"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 50, 256, 32, hWnd, (HMENU)100, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		hButton2 = CreateWindow(TEXT("BUTTON"), TEXT("ƒ[ƒ}Žš"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 90, 256, 32, hWnd, (HMENU)101, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == 100)
		{
			HIMC hIMC = ImmGetContext(hEdit);
			if (hIMC)
			{
				if (ImmGetOpenStatus(hIMC))
				{
					ImmSetOpenStatus(hIMC, TRUE);
					ImmSetConversionStatus(hIMC, 9, IME_CMODE_ROMAN);
					ImmSetOpenStatus(hIMC, FALSE);
				}
				ImmReleaseContext(hEdit, hIMC);
			}
		}
		else if (LOWORD(wParam) == 101)
		{
			HIMC hIMC = ImmGetContext(hEdit);
			if (hIMC)
			{
				if (ImmGetOpenStatus(hIMC))
				{
					ImmSetOpenStatus(hIMC, TRUE);
					ImmSetConversionStatus(hIMC, 25, IME_CMODE_ROMAN);
					ImmSetOpenStatus(hIMC, FALSE);
				}
				ImmReleaseContext(hEdit, hIMC);
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR pCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(
		szClassName,
		TEXT("Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
		);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
