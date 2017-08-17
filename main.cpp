#include <windows.h>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include "resource.h"
using namespace std;

HINSTANCE hInst;
HWND hwnd;
COLORREF CFC = RGB(0,0,0), CBC = RGB(255,255,255);
COLORREF CBCO,CFCO;

void GetLargestDisplayMode (int * pcxBitmap, int * pcyBitmap)
{
     DEVMODE devmode ;
     int     iModeNum = 0 ;

     * pcxBitmap = * pcyBitmap = 0 ;

     ZeroMemory (&devmode, sizeof (DEVMODE)) ;
     devmode.dmSize = sizeof (DEVMODE) ;

     while (EnumDisplaySettings (NULL, iModeNum++, &devmode))
     {
          * pcxBitmap = max (* pcxBitmap, (int) devmode.dmPelsWidth) ;
          * pcyBitmap = max (* pcyBitmap, (int) devmode.dmPelsHeight) ;
     }
}

INT_PTR CALLBACK DlgProcF(HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HWND hR,hG,hB,hC;
    hR = GetDlgItem(hWndDlg,ID_R);
    hG = GetDlgItem(hWndDlg,ID_G);
    hB = GetDlgItem(hWndDlg,ID_B);
    hC = GetDlgItem(hWndDlg,IDM_FCOLOR);
    bool Apply = false;
    switch(uMsg)
    {
        case WM_INITDIALOG:
        {
            SetWindowText(hR, "0");
            SetWindowText(hG, "0");
            SetWindowText(hB, "0");
        }
        return 1;
        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            case ID_SET:
                {
                    CFCO = CFC;
                    LPSTR R = new char[4],G=new char[4],B = new char[4];
                    GetWindowText(hR,R,4);
                    GetWindowText(hG,G,4);
                    GetWindowText(hB,B,4);
                    int r = atoi(R),g = atoi(G),b = atoi(B);
                    CFC = RGB(r,g,b);
                    CFC = CFCO;
                    break;
                }
            case ID_SET_APPLY:
                {
                    LPSTR R = new char[3],G=new char[3],B = new char[3];
                    GetWindowText(hR,R,4);
                    GetWindowText(hG,G,4);
                    GetWindowText(hB,B,4);
                    int r = atoi(R),g = atoi(G),b = atoi(B);
                    ::CFC = RGB(r,g,b);
                    EndDialog(hWndDlg,0);
                    break;
                }
            }
        }
        return 1;
        case WM_CLOSE:
        {
            EndDialog(hWndDlg, 0);
        }
        return 1;
    }
    return 0;
}

INT_PTR CALLBACK DlgProcB(HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HWND hR,hG,hB,hC;
    hR = GetDlgItem(hWndDlg,ID_R);
    hG = GetDlgItem(hWndDlg,ID_G);
    hB = GetDlgItem(hWndDlg,ID_B);
    hC = GetDlgItem(hWndDlg,IDM_BCOLOR);
    bool Apply = false;
    switch(uMsg)
    {
        case WM_INITDIALOG:
        {
            SetWindowText(hR, "255");
            SetWindowText(hG, "255");
            SetWindowText(hB, "255");
        }
        return 1;
        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            case ID_SET:
                {
                    LPSTR R = new char[4],G=new char[4],B = new char[4];
                    GetWindowText(hR,R,4);
                    GetWindowText(hG,G,4);
                    GetWindowText(hB,B,4);
                    int r = atoi(R),g = atoi(G),b = atoi(B);
                    //MessageBox(NULL,R,"",MB_OK);
                    //MessageBox(NULL,G,"",MB_OK);
                    //MessageBox(NULL,B,"",MB_OK);
                    CBC = RGB(r,g,b);
                    Apply = true;
                    InvalidateRect(hwnd, NULL, FALSE);
                    break;
                }
            case ID_SET_APPLY:
                {
                    LPSTR R = new char[3],G=new char[3],B = new char[3];
                    GetWindowText(hR,R,4);
                    GetWindowText(hG,G,4);
                    GetWindowText(hB,B,4);
                    int r = atoi(R),g = atoi(G),b = atoi(B);
                    ::CBC = RGB(r,g,b);
                    InvalidateRect(hwnd, NULL, TRUE);
                    EndDialog(hWndDlg,0);
                    break;
                }
            }
        }
        return 1;
        case WM_CLOSE:
        {
            EndDialog(hWndDlg, 0);
        }
        return 1;
    }
    return 0;
}

int OnCommand(HWND hWnd, int iID, int iEvent, HWND hWndControl, int& csize, int& crsize,COLORREF& CFC,COLORREF& CBC)
{
    switch (iID)
    {
        case IDM_FILE_EXIT:
			{
			    PostQuitMessage(WM_QUIT);
                break;
			}
        case ID_BCOLOR:
            {
                DialogBox(hInst,MAKEINTRESOURCE(DLG_BCOL),NULL,(DLGPROC)DlgProcB);
                break;
            }
        case ID_FCOLOR:
            {
                DialogBox(hInst,MAKEINTRESOURCE(DLG_FCOL),hWnd,(DLGPROC)DlgProcF);
                break;
            }
        case ID_PEN_PLUS:
            {
                if(csize<40)
                    csize++;
                else
                {
                    int MsgID = MessageBox(hWnd,(LPCSTR)"Maximum Size !\nPen Set to MAX !",(LPCSTR)"Brush Size Error",MB_OK|MB_ICONWARNING);
                    switch(MsgID)
                    {
                    case IDOK:
                        {
                            break;
                        }
                    }
                }
                break;
            }
        case ID_ERASER_PLUS:
            {
                if(crsize<100)
                    crsize++;
                else
                {
                    int MsgID = MessageBox(hWnd,(LPCSTR)"Maximum Size !\nRubber Set to MAX !",(LPCSTR)"Rubber Size Error",MB_OK|MB_ICONWARNING);
                    switch(MsgID)
                    {
                    case IDOK:
                        {
                            break;
                        }
                    }
                }
                break;
            }
        case ID_PEN_MINUS:
            {
                if(csize>1)
                    csize--;
                else
                {
                    int MsgID = MessageBox(hWnd,(LPCSTR)"Minimum Size !\nPen Set to MIN !",(LPCSTR)"Brush Size Error",MB_OK|MB_ICONWARNING);
                    switch(MsgID)
                    {
                    case IDOK:
                        {
                            break;
                        }
                    }
                }
                break;
            }
        case ID_ERASER_MINUS:
            {
                if(crsize>1)
                    crsize--;
                else
                {
                    int MsgID = MessageBox(hWnd,(LPCSTR)"Minimum Size !\nRubber Set to MIN !",(LPCSTR)"Rubber Size Error",MB_OK|MB_ICONWARNING);
                    switch(MsgID)
                    {
                    case IDOK:
                        {
                            break;
                        }
                    }
                }
            }
    }
	return 0;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static BOOL    fLeftButtonDown, fRightButtonDown;
     static HBITMAP hBitmap ;
     static HDC     hdcMem ;
     static HPEN hPen;
     static HPEN hEraser;
     static int     cxBitmap, cyBitmap, cxClient, cyClient, xMouse, yMouse ;
     static int csize = 1 , crsize = 1;
     static HMENU hsysm;
     HDC            hdc ;
     PAINTSTRUCT    ps ;
     static HCURSOR curs;
     HMENU hMenu, hMenuTrackPopup;

     switch (message)
     {
    case WM_ERASEBKGND:
	 {
		 HPEN pen;
		 HBRUSH	brush;
		 RECT rect;

		 pen = CreatePen(PS_SOLID, 1, CBC);
		 brush = CreateSolidBrush(CBC);
		 SelectObject((HDC)wParam, pen);
		 SelectObject((HDC)wParam, brush);

		 GetClientRect(hwnd, &rect);

		 Rectangle((HDC)wParam, rect.left, rect.top, rect.right, rect.bottom);
		 return 0;
	}
    case WM_COMMAND:
        {
            int wmId    = LOWORD(wParam);
			int wmEvent = HIWORD(wParam);
			LRESULT lResult = OnCommand(hwnd, wmId, wmEvent, (HWND)lParam, csize, crsize,CFC,CBC);
			return lResult;
        }
    case WM_CONTEXTMENU:
        {
            if( (hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_POPUP))) == NULL )
                return 0;
            hMenuTrackPopup = GetSubMenu(hMenu, 0);
            TrackPopupMenu(hMenuTrackPopup, TPM_LEFTALIGN | TPM_RIGHTBUTTON, LOWORD(lParam), HIWORD(lParam),0,hwnd,NULL);
            break;
        }
    case WM_CHAR:
        {
            if(wParam == VK_ESCAPE)
                exit(0);
            if(wParam == 'c')
            {
                InvalidateRect(hwnd,NULL,TRUE);
            }
            return 0;
        }
    case WM_CREATE:
        {
            hsysm = GetSystemMenu(hwnd,FALSE);
            RemoveMenu(hsysm,0,MF_BYPOSITION);
            GetLargestDisplayMode (&cxBitmap, &cyBitmap) ;
            hdc = GetDC (hwnd) ;
            hBitmap = CreateCompatibleBitmap (hdc, cxBitmap, cyBitmap) ;
            hdcMem  = CreateCompatibleDC (hdc) ;
            ReleaseDC (hwnd, hdc) ;
            if (!hBitmap)       // no memory for bitmap
            {
                DeleteDC (hdcMem) ;
                return -1 ;
            }
            SelectObject (hdcMem, hBitmap) ;
            PatBlt (hdcMem, 0, 0, cxBitmap, cyBitmap, WHITENESS) ;
            return 0 ;
        }
    case WM_SIZE:
        {
            cxClient = LOWORD (lParam) ;
            cyClient = HIWORD (lParam) ;
            return 0 ;
        }
    case WM_LBUTTONDOWN:
        {
            if (!fRightButtonDown)
               SetCapture (hwnd) ;

            xMouse = LOWORD (lParam) ;
            yMouse = HIWORD (lParam) ;
            fLeftButtonDown = TRUE ;
            return 0 ;
        }
    case WM_LBUTTONUP:
        {
            if (fLeftButtonDown)
               SetCapture (NULL) ;
            fLeftButtonDown = FALSE ;
            return 0 ;
        }
    case WM_RBUTTONDOWN:
        {
            curs = LoadCursor(::hInst,MAKEINTRESOURCE(IDC_ERASER));
            SetCursor(curs);
            if (!fLeftButtonDown)
               SetCapture (hwnd) ;
            xMouse = LOWORD (lParam) ;
            yMouse = HIWORD (lParam) ;
            fRightButtonDown = TRUE ;
            return 0 ;
        }
    case WM_RBUTTONUP:
        {
            if (fRightButtonDown)
               SetCapture (NULL) ;
            fRightButtonDown = FALSE ;
            return 0 ;
        }
    case WM_MOUSEMOVE:
        {
            if (!fLeftButtonDown && !fRightButtonDown)
               return 0 ;
            hdc = GetDC (hwnd) ;
            hPen = CreatePen(PS_SOLID,csize,CFC);
            hEraser = CreatePen(PS_SOLID,crsize,CBC);
            SelectObject (hdc,fLeftButtonDown?hPen:hEraser) ;
            SelectObject (hdcMem,fLeftButtonDown?hPen:hEraser) ;
            MoveToEx (hdc,    xMouse, yMouse, NULL) ;
            MoveToEx (hdcMem, xMouse, yMouse, NULL) ;
            xMouse = (short) LOWORD (lParam) ;
            yMouse = (short) HIWORD (lParam) ;
            LineTo (hdc,    xMouse, yMouse) ;
            LineTo (hdcMem, xMouse, yMouse) ;
            ReleaseDC (hwnd, hdc) ;
            return 0 ;
        }
    case WM_PAINT:
        {
            hdc = BeginPaint(hwnd, &ps);
	        SetBkColor(GetDC(hwnd), CBC);
	        EndPaint(hwnd, &ps);
            return 0;
        }
    case WM_DESTROY:
        {
            DeleteDC (hdcMem) ;
            DeleteObject (hBitmap) ;
            PostQuitMessage (0) ;
            return 0 ;
        }
     }
     return DefWindowProc (hwnd, message, wParam, lParam);
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR CmdLine, int iCmdShow)
{
     ::hInst = hInstance;
     static TCHAR AppName [] = TEXT ("| GDI PAINT - Kinshuk Vasisht |") ;
     MSG          msg ;
     WNDCLASS     wndclass ;

     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON)) ;
     wndclass.hCursor       = LoadCursor (hInstance,MAKEINTRESOURCE(IDC_PEN)) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = MAKEINTRESOURCE(IDR_MAIN_MENU); ;
     wndclass.lpszClassName = AppName ;

     if (!RegisterClass (&wndclass))
     {
          MessageBox (NULL, TEXT ("This program requires Windows NT or Greater!"), AppName, MB_ICONERROR) ;
          return 0 ;
     }
     hwnd = CreateWindow (AppName,
                          TEXT ("| GDI PAINT - Kinshuk Vasisht |"),
                          WS_OVERLAPPEDWINDOW,
                          0,
                          0,
                          1370,
                          725,
                          NULL,
                          NULL,
                          hInstance,
                          NULL) ;
     if (hwnd == NULL)
     {
          MessageBox (NULL, TEXT ("Not enough memory!"), AppName, MB_ICONERROR) ;
          return 0 ;
     }
     HACCEL haccel = LoadAccelerators(hInstance,MAKEINTRESOURCE(IDR_ACCEL1));
     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;
     while (GetMessage (&msg, NULL, 0, 0))
     {
          if(!TranslateAccelerator(hwnd,haccel,&msg))
          {
                TranslateMessage (&msg) ;
                DispatchMessage (&msg) ;
          }
     }
     return msg.wParam ;
}
