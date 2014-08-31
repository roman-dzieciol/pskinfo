#pragma once

#include "PSKTypes.h"


template <class HeaderType, class ItemType>
struct PSKBlock
{
	HeaderType Header;
	vector<ItemType> Array;
};


class PSKArchive
{
public:
	fstream File;
	wstring FileName;

public:
	PSKArchive(const wstring& FileName);

public:
	void Serialize( void* buffer, size_t count );

public:
	friend void operator << ( PSKArchive& A, FLOAT& D )		{ A.Serialize( &D, sizeof(FLOAT) );  }
	friend void operator << ( PSKArchive& A, INT& D )		{ A.Serialize( &D, sizeof(INT) );  }
	friend void operator << ( PSKArchive& A, DWORD& D )		{ A.Serialize( &D, sizeof(DWORD) );  }
	friend void operator << ( PSKArchive& A, _WORD& D )		{ A.Serialize( &D, sizeof(_WORD) );  }
	friend void operator << ( PSKArchive& A, BYTE& D )		{ A.Serialize( &D, sizeof(BYTE) );  }

	template <class HeaderType, class ItemType>
	friend void operator << ( PSKArchive& A, PSKBlock<HeaderType,ItemType>& D )		
	{ 
		A << D.Header;
		D.Array.resize(D.Header.DataCount);

		for( auto it=D.Array.begin(); it!=D.Array.end(); ++it )
		{
			A.Serialize( &(*it), sizeof(ItemType) );  
		}
		
		for_each(D.Array.begin(), D.Array.end(), [&](ItemType i) {
			//total += x * value * this->some_func();
			A.Serialize( &i, sizeof(ItemType) );  
		});
	}
};
