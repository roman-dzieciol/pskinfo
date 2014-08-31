#include "StdAfx.h"
#include "UnrealAnimDataStructs.h"
#include "PSK.h"



PSK::PSK( const wstring& FileName ) : PSKArchive(FileName)
{
	Load();
}

void PSK::Load()
{
	*this << GeneralHeader;
	*this << Points;
	*this << Wedges;
	*this << Faces;
	*this << Materials;
	*this << Bones;
	*this << Influences;

	cout << "done" << endl;
	CheckInfluences();
}

void PSK::CheckInfluences()
{
	vector<DWORD> InfluencesPerBone = vector<DWORD>(Bones.Header.DataCount, 0);
	vector<DWORD> InfluencesPerPoint = vector<DWORD>(Points.Header.DataCount, 0);

	for( auto it=Influences.Array.begin(); it!=Influences.Array.end(); ++it )
	{
		if( (strstr(Bones.Array[(*it).BoneIndex].Name, "_IK_" ) != NULL || (*it).BoneIndex == 0) && (*it).Weight > 0 )
		{
			printf("Invalid influence found! Bone %u, Point %u\n", (*it).BoneIndex, (*it).PointIndex);

		}
	

		if( (*it).Weight <= 0.000001f )
		{
			printf("Zero weight influence found! Bone %u, Point %u\n", (*it).BoneIndex, (*it).PointIndex);
		}

		++(InfluencesPerBone.at((*it).BoneIndex));
		++(InfluencesPerPoint.at((*it).PointIndex));
	}

	printf("\nBone influences\n");
	for( auto it=InfluencesPerBone.begin(); it!=InfluencesPerBone.end(); ++it )
	{
		static int counter = 0;
		const string name(Bones.Array[counter].Name);
		if( *it != 0 )
			printf("%u\t%u\t(%s)\n", counter, *it, name.c_str() );
		else
			printf("%u\tNONE\t(%s)\n", counter, name.c_str() );
		++counter;
	}

	printf("\nPoint influences\n");
	for( auto it=InfluencesPerPoint.begin(); it!=InfluencesPerPoint.end(); ++it )
	{
		static int counter = 0;
		if( *it == 0 )
			printf("%u\t%u\n", counter, *it );
		++counter;
	}

	cout << "done" << endl;
}