#include "winnls.h"
#include "shobjidl.h"
#include "objbase.h"
#include "objidl.h"
#include "shlguid.h"


class FileShortcut
{
public:
	static bool create(
		const WCHAR* srcPath,
		const WCHAR* lnkPath,
		const WCHAR* desc);

	static bool create(
		const WCHAR* srcPath,
		const WCHAR* lnkPath);
};


bool FileShortcut::create(
	const WCHAR* srcPath,
	const WCHAR* lnkPath,
	const WCHAR* desc)
{
	HRESULT hres;

	IShellLink* psl;
	hres = CoCreateInstance(
		CLSID_ShellLink,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IShellLink,
		(LPVOID*)&psl);

	if (!SUCCEEDED(hres))
		return false;

	psl->SetPath(srcPath);
	psl->SetDescription(desc);

	IPersistFile* ppf;
	hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);

	if (SUCCEEDED(hres))
	{
		hres = ppf->Save(lnkPath, TRUE);
		ppf->Release();
	}
	psl->Release();

	return true;
}

bool FileShortcut::create(
	const WCHAR* srcPath,
	const WCHAR* lnkPath)
{
	return Create(srcPath, lnkPath, 0);
}
