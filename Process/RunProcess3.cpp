#include "stdafx.h"

#include <iostream>
#include <string>

#include <Windows.h>

// コンソールなし
// プロセス終了待機
// サブプロセスの出力を文字列で返す
// プロセスの戻り値を返す
DWORD systemNCRet(const std::string& cmd, std::string& stdOut)
{
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = 0;
	sa.bInheritHandle = TRUE;

	HANDLE read, write;
	if (!CreatePipe(&read, &write, &sa, 0))
		return 0;

	STARTUPINFO si;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdOutput = write;

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

	for (;;) {
		DWORD rest;
		PeekNamedPipe(read, NULL, 0, NULL, &rest, NULL);
		if (rest == 0)
			break;

		static const int bufSz = 1024;
		DWORD len;
		char buf[bufSz + 1] = {0};
		ReadFile(read, buf, bufSz, &len, NULL);
		stdOut += buf;
	}

	CloseHandle(read);
	CloseHandle(write);

	return code[0];
}
