#include <Windows.h>
#include "Function.h"
#include "Classes.h"

#pragma warning(disable:4996)

static HWND hEdit = NULL;
HINSTANCE savehinst = NULL;
static HWND hEdit2 = NULL;
static HWND hEditR = NULL;
static HWND hEditG = NULL;
static HWND hEditB = NULL;
static HWND hEditCursorPosX = NULL;
static HWND hEditCursorPosY = NULL;



int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
	MSG msg{};
	HWND hwnd{};
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = [](HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam)->LRESULT
	{
		
		switch (uMsg)
		{
		case WM_CREATE:
		{
			CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(always_coord), NULL, NULL, NULL);

			hEdit = CreateWindowW(L"EDIT", L" ", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | WS_BORDER | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE, 100, 0, 400, 600, hwnd, NULL, NULL, NULL);

			hEditR = CreateWindowW(L"EDIT", L" ", WS_CHILD | WS_VISIBLE | ES_READONLY, 0, 0, 70, 25, hwnd, NULL, NULL, NULL);
			hEditG = CreateWindowW(L"EDIT", L" ", WS_CHILD | WS_VISIBLE | ES_READONLY, 0, 25, 70, 25, hwnd, NULL, NULL, NULL);
			hEditB = CreateWindowW(L"EDIT", L" ", WS_CHILD | WS_VISIBLE | ES_READONLY, 0, 50, 70, 25, hwnd, NULL, NULL, NULL);
			hEditCursorPosX = CreateWindowW(L"EDIT", L" ", WS_CHILD | WS_VISIBLE | ES_READONLY, 0, 75, 70, 25, hwnd, NULL, NULL, NULL);
			hEditCursorPosY = CreateWindowW(L"EDIT", L" ", WS_CHILD | WS_VISIBLE | ES_READONLY, 0, 100, 70, 25, hwnd, NULL, NULL, NULL);

		}
		return 0;

		case WM_DESTROY:
		{
			PostQuitMessage(EXIT_SUCCESS);
		}
		return 0;
		}
		return DefWindowProc(hwnd, uMsg, wParam, lparam);
	};
	wc.lpszClassName = "MyappClass";
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wc))
		return EXIT_FAILURE;

	hwnd = CreateWindow(wc.lpszClassName, "Запись движений!", WS_OVERLAPPED|WS_SYSMENU, 0, 0, 500, 600, nullptr, nullptr, wc.hInstance, nullptr);


	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return static_cast<int>(msg.wParam);
}

void appendmessage(int newer, HWND hwnd)
{
	TCHAR swap[256] = "";

	itoa(newer, swap, 10);

	SendMessage(hwnd, EM_SETSEL, 0, -1);
	SendMessage(hwnd, EM_SETSEL, -1, -1);
	SendMessage(hwnd, EM_REPLACESEL, 0, (LPARAM)TEXT(swap));

}
void appendmessage(LPCTSTR newText, HWND hwnd)
{
	SendMessage(hwnd, EM_SETSEL, 0, -1);
	SendMessage(hwnd, EM_SETSEL, -1, -1);
	SendMessage(hwnd, EM_REPLACESEL, 0, (LPARAM)TEXT(newText));

}

void always_coord()
{
	POINT P;
	while (true)
	{
		GetCursorPos(&P);
		CHAR STR[] = { " " };

		SetWindowText(hEditR, STR);
		SetWindowText(hEditG, STR);
		SetWindowText(hEditB, STR);
		SetWindowText(hEditCursorPosX, STR);
		SetWindowText(hEditCursorPosY, STR);

		HDC dng2 = GetDC(NULL);
		COLORREF b = GetPixel(dng2, P.x, P.y);
		appendmessage("\r X: \n", hEditCursorPosX);
		appendmessage((int)P.x, hEditCursorPosX);
		appendmessage("\r Y: \n", hEditCursorPosY);
		appendmessage((int)P.y, hEditCursorPosY);


		appendmessage("\r R: \n", hEditR);
		appendmessage((int)GetRValue(b), hEditR);
		appendmessage("\r G: \n", hEditG);
		appendmessage((int)GetGValue(b), hEditG);
		appendmessage("\r B: \n", hEditB);
		appendmessage((int)GetBValue(b), hEditB);
		Sleep(300);



	}
}
void Script()
{
	script scr;
	



}