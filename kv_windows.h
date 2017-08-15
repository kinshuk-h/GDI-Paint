#ifndef KV_WINDOWS_H_INCLUDED
#define KV_WINDOWS_H_INCLUDED

///External Define to indicate Windows Version...
#define _WIN32_WINNT 0x0500

#include<windows.h>
#include<iostream>

/// Basic Colors - FOREGROUND

#define RED            FOREGROUND_RED|FOREGROUND_INTENSITY
#define BROWN          FOREGROUND_RED
#define GREEN          FOREGROUND_GREEN|FOREGROUND_INTENSITY
#define DARK_GREEN     FOREGROUND_GREEN
#define BLUE           FOREGROUND_BLUE|FOREGROUND_INTENSITY
#define DARK_BLUE      FOREGROUND_BLUE
#define YELLOW         FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY
#define TURQUOISE      FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY
#define DARK_TURQUOISE FOREGROUND_GREEN|FOREGROUND_BLUE
#define PINK           FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY
#define PURPLE         FOREGROUND_BLUE|FOREGROUND_RED
#define OLIVE          FOREGROUND_GREEN|FOREGROUND_RED
#define WHITE          FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY
#define GRAY           FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE
#define DARK_GRAY      FOREGROUND_INTENSITY
#define BLACK          0

/// Basic Colors - BACKGROUND

#define BGRED            BACKGROUND_RED|BACKGROUND_INTENSITY
#define BGBROWN          BACKGROUND_RED
#define BGGREEN          BACKGROUND_GREEN|BACKGROUND_INTENSITY
#define BGDARK_GREEN     BACKGROUND_GREEN
#define BGBLUE           BACKGROUND_BLUE|BACKGROUND_INTENSITY
#define BGDARK_BLUE      BACKGROUND_BLUE
#define BGYELLOW         BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_INTENSITY
#define BGTURQUOISE      BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY
#define BGDARK_TURQUOISE BACKGROUND_GREEN|BACKGROUND_BLUE
#define BGPINK           BACKGROUND_BLUE|BACKGROUND_RED|BACKGROUND_INTENSITY
#define BGPURPLE         BACKGROUND_BLUE|BACKGROUND_RED
#define BGOLIVE          BACKGROUND_GREEN|BACKGROUND_RED
#define BGWHITE          BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_BLUE|BACKGROUND_INTENSITY
#define BGGRAY           BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_BLUE
#define BGDARK_GRAY      BACKGROUND_INTENSITY

using namespace std;

HANDLE out=GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE in =GetStdHandle(STD_INPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;
WORD ORIGINAL;
HWND CONSOLE;
RECT R;
COORD CONSOLECOORD;
///Single Character Width
const double cW = 837.0/80.0;
///Single Character Height
const double cH = 523.0/30.0;

void GetDefault()
{
    GetConsoleScreenBufferInfo(out,&csbi);
    ::ORIGINAL=csbi.wAttributes;
    ::CONSOLE=GetConsoleWindow();
    GetWindowRect(CONSOLE, &R);
    R.left=0;
    R.top=0;
    CONSOLECOORD.X=0;
    CONSOLECOORD.Y=0;
}

void SetConsoleOriginalColor()
{
    SetConsoleTextAttribute(out,ORIGINAL);
}

void SetConsoleColor(WORD COLOR)
{
    SetConsoleTextAttribute(out,COLOR);
}

void SetConsoleOriginalSize()
{
    R.left=350;
    R.right=R.left+80;
    R.top=0;
    R.bottom=R.top+25;
    MoveWindow(CONSOLE,R.left,R.top,80,25,FALSE);
    COORD BufferCoord = {SHORT(80),SHORT(50)};
    SetConsoleScreenBufferSize(out,BufferCoord);
    SMALL_RECT SIZE = {0,0,79,24};
    SetConsoleWindowInfo(out,TRUE,&SIZE);
}

void SetConsoleSize(int w, int h, int rl=350)
{
    R.left=rl;
    R.right=R.left+w;
    R.top=0;
    R.bottom=R.top+h;
    MoveWindow(CONSOLE,R.left,R.top,w,h,FALSE);
    COORD BufferCoord = {SHORT(w),SHORT(h+10)};
    SetConsoleScreenBufferSize(out,BufferCoord);
    SMALL_RECT SIZE = {0,0,SHORT(w-1),SHORT(h-1)};
    SetConsoleWindowInfo(out,TRUE,&SIZE);
}

void Head(ostream& obj,string name,unsigned int mx_width,char sym1='-',char sym2='|')
{
    for(unsigned int i=1;i<=mx_width;i++)
        obj<<sym1;
    if(name.length()<(mx_width))
    {
        obj<<sym2;
        for(unsigned int i=1;i<=(mx_width-2-name.length())/2;i++) obj<<" ";
        if(name.length()%2==0)
            obj<<name;
        else
            obj<<name<<" ";
        for(unsigned int i=1;i<=(mx_width-2-name.length())/2;i++) obj<<" ";
        obj<<sym2;
    }
    else
    {
        obj<<name;
    }
    for(unsigned int i=1;i<=mx_width;i++)
        obj<<sym1;
}

void SetCursorAt(int X,int Y)
{
    CONSOLECOORD.X=X;
    CONSOLECOORD.Y=Y;
    SetConsoleCursorPosition(out,CONSOLECOORD);
}

string GetEXEAddress()
{
    HMODULE hModule = GetModuleHandleA(NULL);
    TCHAR path[MAX_PATH];
    GetModuleFileNameA(hModule, path, MAX_PATH);
    string a;
    a.assign(path);
    return a;
}

string GetEXEDrive()
{
    HMODULE hModule = GetModuleHandleA(NULL);
    TCHAR path[MAX_PATH];
    GetModuleFileNameA(hModule, path, MAX_PATH);
    string a;
    a.assign(path);
    a.resize(2);
    return a;
}

#endif // KV_WINDOWS_H_INCLUDED
