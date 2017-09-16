#include "stdafx.h"
#include "ShellUtil.h"

#include <QFile>
#include <QString>



bool moveToTrashbox(const QString& filepath)
{
	if (!QFile(filepath).exists())
		return false;

	std::wstring ws;

	ws.resize(filepath.size() * 2);
	filepath.toWCharArray(&ws[0]);

	SHFILEOPSTRUCT d = {0};
	d.pFrom = &ws[0];
	d.wFunc = FO_DELETE;
	d.pTo   = NULL;

	d.fFlags =
		FOF_SILENT |
		FOF_ALLOWUNDO |
		FOF_NOERRORUI |
		FOF_NOCONFIRMATION |
		FOF_NO_CONNECTED_ELEMENTS;

	int ret = SHFileOperation(&d);
	return (ret == 0);
}
