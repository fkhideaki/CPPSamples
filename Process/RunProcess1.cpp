#include "stdafx.h"

#include <iostream>
#include <string>

#include <Windows.h>

// コンソールなし
// プロセス終了待機
// プロセスの戻り値を返す
DWORD systemNC(const std::string& cmd)
{
	STARTUPINFO si;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES;

	PROCESS_INFORMATION pi;
	CreateProcess(
		NULL,
		const_cast<char*>(cmd.c_str()),
		NULL,
		NULL,
		TRUE,
		CREATE_NO_WINDOW,
		NULL,
		NULL,
		&si,
		&pi);

	WaitForInputIdle(pi.hProcess, INFINITE);
	WaitForSingleObject(pi.hProcess, INFINITE);

	DWORD code[1];
	GetExitCodeProcess(pi.hProcess, code);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	return code[0];
}
