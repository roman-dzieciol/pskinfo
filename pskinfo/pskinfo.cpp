// pskinfo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "StringConversion.h"
#include "PSK.h"

int wmain(int argc, wchar_t* argv[])
{
	try
	{
		if(argc != 2)
		{
			throw vwexception(L"usage: %S filename.psk", argv[0]);
		}

		wstring filename(argv[1]);
		wcout << filename << endl;

		PSK pskfile(argv[1]);
	}
	catch(exception &e)
	{
		printf("Exception: %s", e.what());
		return -1;
	}
	catch(vwexception &e)
	{
		wprintf(L"Exception: %S", e.what());
		return -1;
	}
	

	return 0;
}

