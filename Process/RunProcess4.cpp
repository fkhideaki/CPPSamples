#include "stdafx.h"

#include <iostream>
#include <string>

#include <Windows.h>

// コマンド実行
// コンソールあり
// サブプロセスの出力を文字列で返す
int systemRet(const std::string& cmd, std::string& stdOut)
{
	char buf[1024];
	FILE *fp = _popen(cmd.c_str(), "r");
	while (fgets(buf, sizeof(buf), fp)) {
		stdOut += buf;
	}
	return _pclose(fp);
}
