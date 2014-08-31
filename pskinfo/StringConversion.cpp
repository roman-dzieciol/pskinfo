
#include "stdafx.h"
#include "StringConversion.h"

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>

string toNarrowString( const wchar_t* pStr )
{
	// figure out how many narrow characters we are going to get 

	int len = static_cast<int>(wcslen(pStr));
	int nChars = WideCharToMultiByte( CP_UTF8 , 0 , pStr , len , NULL , 0 , NULL , NULL ) ; 

	if ( len == -1 )
		-- nChars ; 
	if ( nChars == 0 )
		return "" ;

	// convert the wide string to a narrow string

	// nb: slightly naughty to write directly into the string like this

	string buf ;
	buf.resize( nChars ) ;
	WideCharToMultiByte( CP_UTF8 , 0 , pStr , len , const_cast<char*>(buf.c_str()) , nChars , NULL , NULL ) ; 

	return buf ; 
}

wstring toWideString( const char* pStr )
{
	// figure out how many wide characters we are going to get 

	int len = static_cast<int>(strlen(pStr));
	int nChars = MultiByteToWideChar( CP_ACP , 0 , pStr , len , NULL , 0 ) ; 
	if ( len == -1 )
		-- nChars ; 
	if ( nChars == 0 )
		return L"" ;

	// convert the narrow string to a wide string 

	// nb: slightly naughty to write directly into the string like this

	wstring buf ;
	buf.resize( nChars ) ; 
	MultiByteToWideChar( CP_ACP , 0 , pStr , len , const_cast<wchar_t*>(buf.c_str()) , nChars ) ; 

	return buf ;
}