// Camecore.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

// Global Variables:
HINSTANCE hInst;								// current instance
char TITLE_NAME[] = "Empty Project";
HWND hwndMain;

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
	BOOL bGameQuite = FALSE;

	//load global values
	LoadGlobal();

	// Initialize global strings
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	hAccelTable = LoadAccelerators(hInstance, NULL);

	//do object register at first place
	RegisterToFactory();

	//bind the registed stuff to LUA
	bind2lua();

	//Init game by LUA
	GameInit();

	// Main message loop:
	while ( !bGameQuite )
	{		
		if ( PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) ) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//graphics render
			if ( g_pCanvas )
			{
				g_pCanvas->Render();
			}
		}

		if( msg.message == WM_QUIT )
			bGameQuite = TRUE;
	}

	return (int)msg.wParam;
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW ;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;//LoadIcon(hInstance, (LPCTSTR)IDI_BOKGARDENCORE);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= TITLE_NAME;
	wcex.hIconSm		= NULL;//LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(TITLE_NAME, TITLE_NAME, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU,
      CW_USEDEFAULT, CW_USEDEFAULT, g_iWindow_Width, g_iWindow_Height, NULL, NULL, hInstance, NULL);
   hwndMain = hWnd;
   RECT clinetrect;
   RECT wndrect;
   GetClientRect( hWnd, &clinetrect );
   GetWindowRect( hWnd, &wndrect );

   int width = g_iWindow_Width + wndrect.right - wndrect.left + clinetrect.left - clinetrect.right;
   int height = g_iWindow_Height + wndrect.bottom - wndrect.top - clinetrect.bottom + clinetrect.top;
   SetWindowPos( hWnd, NULL, 50, 50, width, height, 0 );
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_DESTROY	- post a quit message and return
//
//
const int TIMER_ID_GAME_BASIS  = 1;
const int TIMER_FQT_GAME_BASIS = 20;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	ActionModule &AM = singActionModule::instance();
	switch (message) 
	{
	case WM_CREATE:
		{
			//set basic game timer
			SetTimer( hWnd, TIMER_ID_GAME_BASIS, TIMER_FQT_GAME_BASIS, NULL );
		}
		break;
	case WM_KEYDOWN:
		AM.Generate( KeyDown, wParam, lParam );
		break;
//  there will be create the second action
	case WM_CHAR:
		AM.Generate( CharInput, wParam, lParam );
		break;
	case WM_LBUTTONDOWN:
		AM.Generate( MouseClick, wParam, lParam );
		break;
	case WM_LBUTTONUP:
		AM.Generate( MouseRelease, wParam, lParam );
		break;
	case WM_RBUTTONUP:
		AM.Generate( RMouseRelease, wParam, lParam );
		break;
	case WM_MOUSEMOVE:
		AM.Generate( MouseMove, wParam, lParam );
		break;
	case WM_TIMER:
		switch( wParam )
		{
		case TIMER_ID_GAME_BASIS:
			// action process
			singActionModule::instance().Process();
			//Real time game logic
			singPhaseManager::instance().GetCurrentPhase()->RealTimeLogic();
			singPhaseManager::instance().GetCurrentPhase()->LogicKeyDown();

			//audio refresh
			if ( g_pAudio )
				g_pAudio->RefreshMusic();
			break;

		default:
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}





