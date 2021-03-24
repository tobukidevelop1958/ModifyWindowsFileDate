#include "stdafx.h"
#include "MyGetFileTime.h"

BOOL myGetFileTime(LPCWSTR filename, LPFILETIME lpC, LPFILETIME lpA, LPFILETIME lpW)
{
	HANDLE hFile;

	hFile = CreateFile(filename,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		0);

	if (hFile == INVALID_HANDLE_VALUE) {
		/* failed to open the file */
		return FALSE;
	}
	else {
		/* get time */
		GetFileTime(hFile,
			lpC,
			lpA,
			lpW);
	}
	CloseHandle(hFile);
	return TRUE;
}

BOOL mySetFileTime(LPCWSTR filename, LPFILETIME lpC, LPFILETIME lpA, LPFILETIME lpW)
{
	HANDLE hFile;

	hFile = CreateFile(filename,
		FILE_WRITE_ATTRIBUTES,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		0);

	if (hFile == INVALID_HANDLE_VALUE) {
		/* failed to open the file */
		return FALSE;
	}
	else {
		/* set time */
		if (!SetFileTime(hFile,
			lpC,
			lpA,
			lpW)) {
			CloseHandle(hFile);
			return FALSE;
		}
	}
	CloseHandle(hFile);
	return TRUE;
}

void myDispLastError(LPTSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	return;
}

