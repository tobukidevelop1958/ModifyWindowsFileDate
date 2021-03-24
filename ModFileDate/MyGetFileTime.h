#pragma once
#include <windows.h>
#include <strsafe.h>

BOOL myGetFileTime(LPCWSTR filename, LPFILETIME lpC, LPFILETIME lpA, LPFILETIME lpW);
BOOL mySetFileTime(LPCWSTR filename, LPFILETIME lpC, LPFILETIME lpA, LPFILETIME lpW);
void myDispLastError(LPTSTR lpszFunction);
