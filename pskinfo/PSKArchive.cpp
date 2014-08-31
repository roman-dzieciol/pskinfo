#include "StdAfx.h"
#include "PSKArchive.h"


PSKArchive::PSKArchive( const wstring& FileName ) : FileName(FileName)
{
	File.exceptions(fstream::eofbit | fstream::failbit | fstream::badbit);
	File.open(FileName.c_str(), ios::binary | ios_base::in );
}

void PSKArchive::Serialize( void* buffer, size_t count )
{
	File.read((char*)buffer,count);
}