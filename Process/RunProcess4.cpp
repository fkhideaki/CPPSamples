#include "stdafx.h"

#include <iostream>
#include <string>

#include <Windows.h>

// �R�}���h���s
// �R���\�[������
// �T�u�v���Z�X�̏o�͂𕶎���ŕԂ�
int systemRet(const std::string& cmd, std::string& stdOut)
{
	char buf[1024];
	FILE *fp = _popen(cmd.c_str(), "r");
	while (fgets(buf, sizeof(buf), fp)) {
		stdOut += buf;
	}
	return _pclose(fp);
}
