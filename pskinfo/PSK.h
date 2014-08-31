#pragma once

#include "UnrealAnimDataStructs.h"


class PSK : public PSKArchive
{

public:
	VChunkHeader GeneralHeader;
	
	PSKBlock<VChunkHeader, VPoint> Points;
	PSKBlock<VChunkHeader, VVertex> Wedges;
	PSKBlock<VChunkHeader, VTriangle> Faces;
	PSKBlock<VChunkHeader, VMaterial> Materials;
	PSKBlock<VChunkHeader, VBone> Bones;
	PSKBlock<VChunkHeader, VRawBoneInfluence> Influences;

public:
	PSK(const wstring& FileName);

public:
	void Load();
	void CheckInfluences();
};
