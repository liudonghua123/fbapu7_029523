// Splash screen code
#include "burner.h"

int nSplashTime = 1500;

static HWND hSplashDlg = NULL;
static HANDLE hSplashThread = NULL;
static DWORD dwSplashThreadID = 0;

static 	clock_t StartTime;

static BOOL CALLBACK SplashProc(HWND hDlg, UINT Msg, WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	if (nDisableSplash == 0) {
		if (Msg == WM_INITDIALOG) {
			RECT rect;
			int x, y;

			hSplashDlg = hDlg;

			SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);

			x = 304 + GetSystemMetrics(SM_CXDLGFRAME) * 2 + 6;
			y = 224 + GetSystemMetrics(SM_CYDLGFRAME) * 2 + 6;


			SetForegroundWindow(hDlg);
			SetWindowPos(hDlg, HWND_TOPMOST, (rect.right - rect.left) / 2 - x / 2, (rect.bottom - rect.top) / 2 - y / 2, x, y, 0);
			RedrawWindow(hDlg, NULL, NULL, 0);
			ShowWindow(hDlg, SW_SHOWNORMAL);

			return TRUE;
		}
	}

	return 0;
}

static DWORD WINAPI DoSplash(LPVOID)
{
	MSG msg;

	if (nDisableSplash == 0) {
		// Raise the thread priority for this thread
		SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

		CreateDialog(hAppInst, MAKEINTRESOURCE(IDD_SPLASH), NULL, SplashProc);

		while (GetMessage(&msg, NULL, 0, 0)) {

			// See if we need to end the thread
			if (msg.message == (WM_APP + 0)) {
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DestroyWindow(hSplashDlg);
	}

	return 0;
}

int SplashCreate()
{
	if (nDisableSplash == 0) {
		if (hSplashDlg || !nSplashTime || hSplashThread) {
			return 1;
		}

		hSplashThread = CreateThread(NULL, 0, DoSplash, NULL, THREAD_TERMINATE, &dwSplashThreadID);

		StartTime = clock();
	}

	return 0;
}

void SplashDestroy(bool bForce)
{
	if (hSplashThread) {

		if (!bForce && clock() - nSplashTime < StartTime) {
			return;
		}

		// Signal the splash thread to end
		PostThreadMessage(dwSplashThreadID, WM_APP + 0, 0, 0);

		// Wait for the thread to finish
		if (WaitForSingleObject(hSplashThread, 10000) != WAIT_OBJECT_0) {
			// If the thread doesn't finish within 10 seconds, forcibly kill it
			TerminateThread(hSplashThread, 1);
		}

		hSplashDlg = NULL;

		CloseHandle(hSplashThread);

		hSplashThread = NULL;
		dwSplashThreadID = 0;

	}
}
