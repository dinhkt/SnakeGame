#ifndef NEWGRAPHICS_H
#define NEWGRAPHICS_H

#include<windows.h>
#include<dos.h>
#include<iostream>
#include<stdio.h>
HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); // lay handle cua console hien hanh

/* Ham: gotoxy()
 * Chuc nang: dua con tro den vi tri x, y
 * Tham so: x, y
 * Tra ve: khong
 */
void gotoxy(short x,short y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x,y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}

/* Ham: SetColor()
 * Chuc nang: dat mau cho chu
 * Tham so: color
 * Tra ve: khong
 */
void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

/* Ham: SetBGColor()
 * Chuc nang: dat mau nen cho chu
 * Tham so: color
 * Tra ve: khong
 */
void SetBGColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

/* Ham: NT_SetConsoleDisplayMode()
 * Chuc nang: thiet lap che do hien thi, co full screen hay khong
 * Tham so: hOutputHandle, dwNewMode
 * Tra ve: TRUE or FALSE
 */
BOOL NT_SetConsoleDisplayMode(HANDLE hOutputHandle, DWORD dwNewMode)
{
    typedef BOOL (WINAPI *SCDMProc_t) (HANDLE, DWORD, LPDWORD);
    SCDMProc_t SetConsoleDisplayMode;
    HMODULE hKernel32;
    BOOL bFreeLib = FALSE, ret;
    const char KERNEL32_NAME[] = "kernel32.dll";

    hKernel32 = GetModuleHandleA(KERNEL32_NAME);
    if (hKernel32 == NULL)
    {
        hKernel32 = LoadLibraryA(KERNEL32_NAME);
        if (hKernel32 == NULL)
            return FALSE;

        bFreeLib = TRUE;
    }

    SetConsoleDisplayMode =
        (SCDMProc_t)GetProcAddress(hKernel32, "SetConsoleDisplayMode");
    if (SetConsoleDisplayMode == NULL)
    {
        SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
        ret = FALSE;
    }
    else
    {
        DWORD tmp;
        ret = SetConsoleDisplayMode(hOutputHandle, dwNewMode, &tmp);
    }

    if (bFreeLib)
        FreeLibrary(hKernel32);

    return ret;
}

/* Ham: setFullScreen()
 * Chuc nang: dat che do full screen
 * Tham so: khong
 * Tra ve: khong
 */
void setFullScreen()
{
    NT_SetConsoleDisplayMode( GetStdHandle( STD_OUTPUT_HANDLE ), 1 );
}

/* Ham: exitFullScreen()
 * Chuc nang: thoat khoi full screen
 * Tham so: khong
 * Tra ve: khong
 */
void exitFullScreen()
{
    NT_SetConsoleDisplayMode( GetStdHandle( STD_OUTPUT_HANDLE ), 0 );
}

/* Ham: ShowCur()
 * Chuc nang: an con tro trong console
 * Tham so: CursorVisibility
 * Tra ve: khong
 */
void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = {1, CursorVisibility};
    SetConsoleCursorInfo(handle, &cursor);
}

/* Ham: cls()
 * Chuc nang: xoa man hinh console
 * Tham so: hConsole
 * Tra ve: khong
 */
void cls( HANDLE hConsole )
{
   COORD coordScreen = { 0, 0 };    // home for the cursor
   DWORD cCharsWritten;
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   DWORD dwConSize;

 // Get the number of character cells in the current buffer.

   if( !GetConsoleScreenBufferInfo( hConsole, &csbi ))
      return;
   dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

   // Fill the entire screen with blanks.

   if( !FillConsoleOutputCharacter( hConsole, (TCHAR) ' ',
      dwConSize, coordScreen, &cCharsWritten ))
      return;

   // Get the current text attribute.

   if( !GetConsoleScreenBufferInfo( hConsole, &csbi ))
      return;

   // Set the buffer's attributes accordingly.

   if( !FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
      dwConSize, coordScreen, &cCharsWritten ))
      return;

   // Put the cursor at its home coordinates.

   SetConsoleCursorPosition( hConsole, coordScreen );
}

/* Ham: clearScreen()
 * Chuc nang: xoa man hinh console hien tai
 * Tham so: khong
 * Tra ve: khong
 */
void clearScreen(){
    cls(hCon);
}
#endif // NEWGRAPHICS_H

