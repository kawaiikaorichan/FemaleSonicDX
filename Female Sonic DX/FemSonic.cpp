#include "pch.h"
#include <stdio.h>
#include "IniFile.hpp"
#include <cmath>
#include "stdafx.h"
#include "sstextlist.h"

//Macros
#define ReplacePVM(a, b) helperFunctions.ReplaceFile("system\\" a ".PVM", "system\\" b ".PVM");
NJS_MATERIAL* TemporaryMaterialArray[] = { nullptr };

void __cdecl SetLSDColor()
{
	SetMaterialAndSpriteColor_Float(0.8f, 0.8f, 0.f, 0.7f);
}

extern "C"
{
	uint16_t Sonic_UpperArmIndices_DX[] = {
		0, 2,
		1, 3,
		4, 6,
		5, 7,
	};

	uint16_t Sonic_LowerArmIndices_DX[] = {
		4, 14,
		5, 15,
		1, 11,
		0, 10,
	};

	uint16_t Sonic_KneeIndices_DX[] = {
		0, 2,
		1, 3,
		4, 6,
		5, 7,
	};

	uint16_t Sonic_LegIndices_DX[] = {
		0, 2,
		1, 3,
		4, 6,
		5, 7,
	};

	uint16_t Sonic_ShoeIndices_DX[] = {
		1, 0,
		0, 1,
		31, 26,
		34, 2,
		3, 23,
		30, 22,
		2, 24,
		33, 3,
		32, 25,
	};

	uint16_t Sonic_HandIndices_DX[] = {
		11, 50,
		0, 14,
		12, 13,
		1, 55,
		5, 54,
		8, 12,
		4, 15,
	};

	void __cdecl InitSonicWeldInfo_mod()
	{
		NJS_OBJECT* v0; // ebp@1
		NJS_OBJECT* v1; // ebp@1
		NJS_OBJECT* v2; // ebp@1
		NJS_OBJECT* v3; // ebp@1
		NJS_OBJECT* v4; // edi@1
		NJS_OBJECT* v5; // eax@1

		//The following welds are for Sonic
		SonicWeldInfo[0].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
		SonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
		SonicWeldInfo[0].anonymous_5 = 0;
		SonicWeldInfo[0].VertexBuffer = 0;
		SonicWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_DX) / 2);
		SonicWeldInfo[0].WeldType = 2;
		SonicWeldInfo[0].VertIndexes = Sonic_UpperArmIndices_DX;
		SonicWeldInfo[1].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
		SonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
		SonicWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_DX) / 2);
		SonicWeldInfo[1].WeldType = 2;
		SonicWeldInfo[1].anonymous_5 = 0;
		SonicWeldInfo[1].VertexBuffer = 0;
		SonicWeldInfo[1].VertIndexes = Sonic_LowerArmIndices_DX;
		SonicWeldInfo[2].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
		SonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
		SonicWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_DX) / 2);
		SonicWeldInfo[2].WeldType = 2;
		SonicWeldInfo[2].anonymous_5 = 0;
		SonicWeldInfo[2].VertexBuffer = 0;
		SonicWeldInfo[2].VertIndexes = Sonic_UpperArmIndices_DX;
		SonicWeldInfo[3].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
		v0 = SONIC_OBJECTS[9];
		SonicWeldInfo[3].VertIndexes = Sonic_LowerArmIndices_DX;
		SonicWeldInfo[3].ModelB = v0;
		SonicWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_DX) / 2);
		SonicWeldInfo[3].WeldType = 2;
		SonicWeldInfo[3].anonymous_5 = 0;
		SonicWeldInfo[3].VertexBuffer = 0;
		SonicWeldInfo[4].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
		SonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
		SonicWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_DX) / 2);
		SonicWeldInfo[4].WeldType = 2;
		SonicWeldInfo[4].anonymous_5 = 0;
		SonicWeldInfo[4].VertexBuffer = 0;
		SonicWeldInfo[4].VertIndexes = Sonic_KneeIndices_DX;
		SonicWeldInfo[5].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
		SonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
		SonicWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_DX) / 2);
		SonicWeldInfo[5].WeldType = 2;
		SonicWeldInfo[5].anonymous_5 = 0;
		SonicWeldInfo[5].VertexBuffer = 0;
		SonicWeldInfo[5].VertIndexes = Sonic_LegIndices_DX;
		SonicWeldInfo[6].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
		v1 = SONIC_OBJECTS[18];
		SonicWeldInfo[6].VertIndexes = Sonic_KneeIndices_DX;
		SonicWeldInfo[6].ModelB = v1;
		SonicWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_DX) / 2);
		SonicWeldInfo[6].WeldType = 2;
		SonicWeldInfo[6].anonymous_5 = 0;
		SonicWeldInfo[6].VertexBuffer = 0;
		SonicWeldInfo[7].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
		SonicWeldInfo[7].ModelB = SONIC_OBJECTS[19];
		SonicWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_DX) / 2);
		SonicWeldInfo[7].WeldType = 2;
		SonicWeldInfo[7].anonymous_5 = 0;
		SonicWeldInfo[7].VertexBuffer = 0;
		SonicWeldInfo[7].VertIndexes = Sonic_LegIndices_DX;
		SonicWeldInfo[8].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
		SonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
		SonicWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_DX) / 2);
		SonicWeldInfo[8].WeldType = 2;
		SonicWeldInfo[8].anonymous_5 = 0;
		SonicWeldInfo[8].VertexBuffer = 0;
		SonicWeldInfo[8].VertIndexes = Sonic_ShoeIndices_DX;
		SonicWeldInfo[9].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
		v2 = SONIC_OBJECTS[21];
		SonicWeldInfo[9].VertIndexes = Sonic_ShoeIndices_DX;
		SonicWeldInfo[9].ModelB = v2;
		SonicWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_DX) / 2);
		SonicWeldInfo[9].WeldType = 2;
		SonicWeldInfo[9].anonymous_5 = 0;
		SonicWeldInfo[9].VertexBuffer = 0;
		SonicWeldInfo[10].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[10].ModelA = SONIC_OBJECTS[4];
		SonicWeldInfo[10].ModelB = SONIC_OBJECTS[5];
		SonicWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
		SonicWeldInfo[10].WeldType = 2;
		SonicWeldInfo[10].anonymous_5 = 0;
		SonicWeldInfo[10].VertexBuffer = 0;
		SonicWeldInfo[10].VertIndexes = Sonic_HandIndices_DX;
		SonicWeldInfo[11].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[11].ModelA = SONIC_OBJECTS[10];
		SonicWeldInfo[11].ModelB = SONIC_OBJECTS[11];
		SonicWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
		SonicWeldInfo[11].WeldType = 2;
		SonicWeldInfo[11].anonymous_5 = 0;
		SonicWeldInfo[11].VertexBuffer = 0;
		SonicWeldInfo[11].VertIndexes = Sonic_HandIndices_DX;
		SonicWeldInfo[12].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
		SonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
		SonicWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_DX) / 2);
		SonicWeldInfo[12].WeldType = 2;
		SonicWeldInfo[12].anonymous_5 = 0;
		SonicWeldInfo[12].VertexBuffer = 0;
		SonicWeldInfo[12].VertIndexes = Sonic_ShoeIndices_DX;
		SonicWeldInfo[13].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
		SonicWeldInfo[13].ModelB = SONIC_OBJECTS[61];
		SonicWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_DX) / 2);
		SonicWeldInfo[13].WeldType = 2;
		SonicWeldInfo[13].anonymous_5 = 0;
		SonicWeldInfo[13].VertexBuffer = 0;
		SonicWeldInfo[13].VertIndexes = Sonic_ShoeIndices_DX;
		SonicWeldInfo[14].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
		SonicWeldInfo[14].ModelB = SONIC_OBJECTS[63];
		SonicWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_DX) / 2);
		SonicWeldInfo[14].WeldType = 2;
		SonicWeldInfo[14].anonymous_5 = 0;
		SonicWeldInfo[14].VertexBuffer = 0;
		SonicWeldInfo[14].VertIndexes = Sonic_UpperArmIndices_DX;
		SonicWeldInfo[15].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[15].ModelA = SONIC_OBJECTS[5];
		SonicWeldInfo[15].ModelB = 0;
		SonicWeldInfo[15].VertexPairCount = 2;
		SonicWeldInfo[15].WeldType = 4;
		SonicWeldInfo[15].anonymous_5 = 0;
		SonicWeldInfo[15].VertexBuffer = 0;
		SonicWeldInfo[15].VertIndexes = 0;
		SonicWeldInfo[16].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[16].ModelA = SONIC_OBJECTS[11];
		SonicWeldInfo[16].ModelB = 0;
		SonicWeldInfo[16].VertexPairCount = 2;
		SonicWeldInfo[16].WeldType = 5;
		SonicWeldInfo[16].anonymous_5 = 0;
		SonicWeldInfo[16].VertexBuffer = 0;
		SonicWeldInfo[16].VertIndexes = 0;
		SonicWeldInfo[17].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[17].ModelA = SONIC_OBJECTS[59];
		SonicWeldInfo[17].ModelB = 0;
		SonicWeldInfo[17].VertexPairCount = 0;
		SonicWeldInfo[17].WeldType = 7;
		SonicWeldInfo[17].anonymous_5 = 0;
		SonicWeldInfo[17].VertexBuffer = 0;
		SonicWeldInfo[17].VertIndexes = 0;
		SonicWeldInfo[18].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[18].ModelA = SONIC_OBJECTS[61];
		SonicWeldInfo[18].ModelB = 0;
		SonicWeldInfo[18].VertexPairCount = 0;
		SonicWeldInfo[18].WeldType = 6;
		SonicWeldInfo[18].anonymous_5 = 0;
		SonicWeldInfo[18].VertexBuffer = 0;
		SonicWeldInfo[18].VertIndexes = 0;
		SonicWeldInfo[19].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[19].ModelA = SONIC_OBJECTS[16];
		SonicWeldInfo[19].ModelB = 0;
		SonicWeldInfo[19].VertexPairCount = 0;
		SonicWeldInfo[19].WeldType = 6;
		SonicWeldInfo[19].anonymous_5 = 0;
		SonicWeldInfo[19].VertexBuffer = 0;
		SonicWeldInfo[19].VertIndexes = 0;
		SonicWeldInfo[20].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[20].ModelA = SONIC_OBJECTS[21];
		SonicWeldInfo[20].ModelB = 0;
		SonicWeldInfo[20].VertexPairCount = 0;
		SonicWeldInfo[20].WeldType = 7;
		SonicWeldInfo[20].anonymous_5 = 0;
		SonicWeldInfo[20].VertexBuffer = 0;
		SonicWeldInfo[20].VertIndexes = 0;
		SonicWeldInfo[21].BaseModel = SONIC_OBJECTS[0];
		SonicWeldInfo[21].ModelA = SONIC_OBJECTS[45];
		SonicWeldInfo[21].ModelB = 0;
		SonicWeldInfo[21].VertexPairCount = 0;
		SonicWeldInfo[21].WeldType = 8;
		SonicWeldInfo[21].anonymous_5 = 0;
		SonicWeldInfo[21].VertexBuffer = 0;
		SonicWeldInfo[21].VertIndexes = 0;

		//The following welds are for Super Sonic
		SonicWeldInfo[22].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[22].ModelA = SONIC_OBJECTS[23];
		SonicWeldInfo[22].ModelB = SONIC_OBJECTS[24];
		SonicWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_DX) / 2);
		SonicWeldInfo[22].WeldType = 2;
		SonicWeldInfo[22].anonymous_5 = 0;
		SonicWeldInfo[22].VertexBuffer = 0;
		SonicWeldInfo[22].VertIndexes = Sonic_UpperArmIndices_DX;
		SonicWeldInfo[23].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[23].ModelA = SONIC_OBJECTS[24];
		SonicWeldInfo[23].ModelB = SONIC_OBJECTS[25];
		SonicWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_DX) / 2);
		SonicWeldInfo[23].WeldType = 2;
		SonicWeldInfo[23].anonymous_5 = 0;
		SonicWeldInfo[23].VertexBuffer = 0;
		SonicWeldInfo[23].VertIndexes = Sonic_LowerArmIndices_DX;
		SonicWeldInfo[24].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[24].ModelA = SONIC_OBJECTS[28];
		SonicWeldInfo[24].ModelB = SONIC_OBJECTS[29];
		SonicWeldInfo[24].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_DX) / 2);
		SonicWeldInfo[24].WeldType = 2;
		SonicWeldInfo[24].anonymous_5 = 0;
		SonicWeldInfo[24].VertexBuffer = 0;
		SonicWeldInfo[24].VertIndexes = Sonic_UpperArmIndices_DX;
		SonicWeldInfo[25].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[25].ModelA = SONIC_OBJECTS[29];
		SonicWeldInfo[25].ModelB = SONIC_OBJECTS[30];
		SonicWeldInfo[25].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_DX) / 2);
		SonicWeldInfo[25].WeldType = 2;
		SonicWeldInfo[25].anonymous_5 = 0;
		SonicWeldInfo[25].VertexBuffer = 0;
		SonicWeldInfo[25].VertIndexes = Sonic_LowerArmIndices_DX;
		SonicWeldInfo[26].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[26].ModelA = SONIC_OBJECTS[33];
		SonicWeldInfo[26].ModelB = SONIC_OBJECTS[34];
		SonicWeldInfo[26].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_DX) / 2);
		SonicWeldInfo[26].WeldType = 2;
		SonicWeldInfo[26].anonymous_5 = 0;
		SonicWeldInfo[26].VertexBuffer = 0;
		SonicWeldInfo[26].VertIndexes = Sonic_KneeIndices_DX;
		SonicWeldInfo[27].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[27].ModelA = SONIC_OBJECTS[34];
		SonicWeldInfo[27].ModelB = SONIC_OBJECTS[35];
		SonicWeldInfo[27].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_DX) / 2);
		SonicWeldInfo[27].WeldType = 2;
		SonicWeldInfo[27].anonymous_5 = 0;
		SonicWeldInfo[27].VertexBuffer = 0;
		SonicWeldInfo[27].VertIndexes = Sonic_LegIndices_DX;
		SonicWeldInfo[28].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[28].ModelA = SONIC_OBJECTS[38];
		v3 = SONIC_OBJECTS[39];
		SonicWeldInfo[28].VertIndexes = Sonic_KneeIndices_DX;
		SonicWeldInfo[28].ModelB = v3;
		SonicWeldInfo[28].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_DX) / 2);
		SonicWeldInfo[28].WeldType = 2;
		SonicWeldInfo[28].anonymous_5 = 0;
		SonicWeldInfo[28].VertexBuffer = 0;
		SonicWeldInfo[29].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[29].ModelA = SONIC_OBJECTS[39];
		SonicWeldInfo[29].ModelB = SONIC_OBJECTS[40];
		SonicWeldInfo[29].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_DX) / 2);
		SonicWeldInfo[29].WeldType = 2;
		SonicWeldInfo[29].anonymous_5 = 0;
		SonicWeldInfo[29].VertexBuffer = 0;
		SonicWeldInfo[29].VertIndexes = Sonic_LegIndices_DX;
		SonicWeldInfo[30].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[30].ModelA = SONIC_OBJECTS[36];
		SonicWeldInfo[30].ModelB = SONIC_OBJECTS[37];
		SonicWeldInfo[30].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_DX) / 2);
		SonicWeldInfo[30].WeldType = 2;
		SonicWeldInfo[30].anonymous_5 = 0;
		SonicWeldInfo[30].VertexBuffer = 0;
		SonicWeldInfo[30].VertIndexes = Sonic_ShoeIndices_DX;
		SonicWeldInfo[31].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[31].ModelA = SONIC_OBJECTS[41];
		SonicWeldInfo[31].ModelB = SONIC_OBJECTS[42];
		SonicWeldInfo[31].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_DX) / 2);
		SonicWeldInfo[31].WeldType = 2;
		SonicWeldInfo[31].anonymous_5 = 0;
		SonicWeldInfo[31].VertexBuffer = 0;
		SonicWeldInfo[31].VertIndexes = Sonic_ShoeIndices_DX;
		SonicWeldInfo[32].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[32].ModelA = SONIC_OBJECTS[31];
		SonicWeldInfo[32].ModelB = SONIC_OBJECTS[32];
		SonicWeldInfo[32].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
		SonicWeldInfo[32].WeldType = 2;
		SonicWeldInfo[32].anonymous_5 = 0;
		SonicWeldInfo[32].VertexBuffer = 0;
		SonicWeldInfo[32].VertIndexes = Sonic_HandIndices_DX;
		SonicWeldInfo[33].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[33].ModelA = SONIC_OBJECTS[26];
		v4 = SONIC_OBJECTS[27];
		SonicWeldInfo[33].anonymous_5 = 0;
		SonicWeldInfo[33].VertexBuffer = 0;
		SonicWeldInfo[33].VertIndexes = Sonic_HandIndices_DX;
		SonicWeldInfo[33].ModelB = v4;
		SonicWeldInfo[33].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
		SonicWeldInfo[33].WeldType = 2;
		SonicWeldInfo[34].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[34].ModelA = SONIC_OBJECTS[31];
		SonicWeldInfo[34].ModelB = SONIC_OBJECTS[32];
		SonicWeldInfo[34].anonymous_5 = 0;
		SonicWeldInfo[34].VertexBuffer = 0;
		SonicWeldInfo[34].VertexPairCount = 4;
		SonicWeldInfo[34].VertIndexes = Sonic_HandIndices_DX;
		SonicWeldInfo[34].WeldType = 2;
		SonicWeldInfo[35].BaseModel = SONIC_OBJECTS[22];
		SonicWeldInfo[35].ModelA = SONIC_OBJECTS[26];
		v5 = SONIC_OBJECTS[27];
		SonicWeldInfo[35].anonymous_5 = 0;
		SonicWeldInfo[35].VertexBuffer = 0;
		SonicWeldInfo[36].BaseModel = 0;
		SonicWeldInfo[36].ModelA = 0;
		SonicWeldInfo[36].ModelB = 0;
		SonicWeldInfo[35].VertIndexes = Sonic_HandIndices_DX;
		SonicWeldInfo[36].VertexPairCount = 0;
		SonicWeldInfo[36].VertexBuffer = 0;
		SonicWeldInfo[35].VertexPairCount = 4;
		SonicWeldInfo[35].ModelB = v5;
		SonicWeldInfo[35].WeldType = 2;
		SonicWeldInfo[36].VertIndexes = 0;
	}

	void __cdecl InitNPCSonicWeldInfo_mod()
	{
		NJS_OBJECT* v0; // ebp@1
		NJS_OBJECT* v1; // ebp@1
		NJS_OBJECT* v2; // ebp@1
		NJS_OBJECT* v3; // ebp@1
		NJS_OBJECT* v4; // eax@1

		NPCSonicWeldInfo[0].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
		NPCSonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
		NPCSonicWeldInfo[0].anonymous_5 = 0;
		NPCSonicWeldInfo[0].VertexBuffer = 0;
		NPCSonicWeldInfo[0].VertIndexes = Sonic_UpperArmIndices_DX;
		NPCSonicWeldInfo[0].WeldType = 2;
		NPCSonicWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_DX) / 2);
		NPCSonicWeldInfo[1].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
		NPCSonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
		NPCSonicWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_DX) / 2);
		NPCSonicWeldInfo[1].WeldType = 2;
		NPCSonicWeldInfo[1].anonymous_5 = 0;
		NPCSonicWeldInfo[1].VertexBuffer = 0;
		NPCSonicWeldInfo[1].VertIndexes = Sonic_LowerArmIndices_DX;
		NPCSonicWeldInfo[2].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
		NPCSonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
		NPCSonicWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_DX) / 2);
		NPCSonicWeldInfo[2].WeldType = 2;
		NPCSonicWeldInfo[2].anonymous_5 = 0;
		NPCSonicWeldInfo[2].VertexBuffer = 0;
		NPCSonicWeldInfo[2].VertIndexes = Sonic_UpperArmIndices_DX;
		NPCSonicWeldInfo[3].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
		v0 = SONIC_OBJECTS[9];
		NPCSonicWeldInfo[3].VertIndexes = Sonic_LowerArmIndices_DX;
		NPCSonicWeldInfo[3].ModelB = v0;
		NPCSonicWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_DX) / 2);
		NPCSonicWeldInfo[3].WeldType = 2;
		NPCSonicWeldInfo[3].anonymous_5 = 0;
		NPCSonicWeldInfo[3].VertexBuffer = 0;
		NPCSonicWeldInfo[4].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
		NPCSonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
		NPCSonicWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_DX) / 2);
		NPCSonicWeldInfo[4].WeldType = 2;
		NPCSonicWeldInfo[4].anonymous_5 = 0;
		NPCSonicWeldInfo[4].VertexBuffer = 0;
		NPCSonicWeldInfo[4].VertIndexes = Sonic_KneeIndices_DX;
		NPCSonicWeldInfo[5].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
		NPCSonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
		NPCSonicWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_DX) / 2);
		NPCSonicWeldInfo[5].WeldType = 2;
		NPCSonicWeldInfo[5].anonymous_5 = 0;
		NPCSonicWeldInfo[5].VertexBuffer = 0;
		NPCSonicWeldInfo[5].VertIndexes = Sonic_LegIndices_DX;
		NPCSonicWeldInfo[6].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
		NPCSonicWeldInfo[6].ModelB = SONIC_OBJECTS[18];
		NPCSonicWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_DX) / 2);
		NPCSonicWeldInfo[6].WeldType = 2;
		NPCSonicWeldInfo[6].anonymous_5 = 0;
		NPCSonicWeldInfo[6].VertexBuffer = 0;
		NPCSonicWeldInfo[6].VertIndexes = Sonic_KneeIndices_DX;
		NPCSonicWeldInfo[7].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
		v1 = SONIC_OBJECTS[19];
		NPCSonicWeldInfo[7].VertIndexes = Sonic_LegIndices_DX;
		NPCSonicWeldInfo[7].ModelB = v1;
		NPCSonicWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_DX) / 2);
		NPCSonicWeldInfo[7].WeldType = 2;
		NPCSonicWeldInfo[7].anonymous_5 = 0;
		NPCSonicWeldInfo[7].VertexBuffer = 0;
		NPCSonicWeldInfo[8].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
		NPCSonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
		NPCSonicWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_DX) / 2);
		NPCSonicWeldInfo[8].WeldType = 2;
		NPCSonicWeldInfo[8].anonymous_5 = 0;
		NPCSonicWeldInfo[8].VertexBuffer = 0;
		NPCSonicWeldInfo[8].VertIndexes = Sonic_ShoeIndices_DX;
		NPCSonicWeldInfo[9].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
		v2 = SONIC_OBJECTS[21];
		NPCSonicWeldInfo[9].VertIndexes = Sonic_ShoeIndices_DX;
		NPCSonicWeldInfo[9].ModelB = v2;
		NPCSonicWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_DX) / 2);
		NPCSonicWeldInfo[9].WeldType = 2;
		NPCSonicWeldInfo[9].anonymous_5 = 0;
		NPCSonicWeldInfo[9].VertexBuffer = 0;
		NPCSonicWeldInfo[10].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
		NPCSonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
		NPCSonicWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
		NPCSonicWeldInfo[10].WeldType = 2;
		NPCSonicWeldInfo[10].anonymous_5 = 0;
		NPCSonicWeldInfo[10].VertexBuffer = 0;
		NPCSonicWeldInfo[10].VertIndexes = Sonic_HandIndices_DX;
		NPCSonicWeldInfo[11].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
		NPCSonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
		NPCSonicWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
		NPCSonicWeldInfo[11].WeldType = 2;
		NPCSonicWeldInfo[11].anonymous_5 = 0;
		NPCSonicWeldInfo[11].VertexBuffer = 0;
		NPCSonicWeldInfo[11].VertIndexes = Sonic_HandIndices_DX;
		NPCSonicWeldInfo[12].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
		NPCSonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
		NPCSonicWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_DX) / 2);
		NPCSonicWeldInfo[12].anonymous_5 = 0;
		NPCSonicWeldInfo[12].VertexBuffer = 0;
		NPCSonicWeldInfo[12].WeldType = 2;
		NPCSonicWeldInfo[12].VertIndexes = Sonic_ShoeIndices_DX;
		NPCSonicWeldInfo[13].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
		v3 = SONIC_OBJECTS[61];
		NPCSonicWeldInfo[13].anonymous_5 = 0;
		NPCSonicWeldInfo[13].VertexBuffer = 0;
		NPCSonicWeldInfo[13].ModelB = v3;
		NPCSonicWeldInfo[13].VertIndexes = Sonic_ShoeIndices_DX;
		NPCSonicWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_DX) / 2);
		NPCSonicWeldInfo[13].WeldType = 2;
		NPCSonicWeldInfo[14].BaseModel = *SONIC_OBJECTS;
		NPCSonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
		v4 = SONIC_OBJECTS[63];
		NPCSonicWeldInfo[14].anonymous_5 = 0;
		NPCSonicWeldInfo[14].VertexBuffer = 0;
		NPCSonicWeldInfo[15].BaseModel = 0;
		NPCSonicWeldInfo[15].ModelA = 0;
		NPCSonicWeldInfo[15].ModelB = 0;
		NPCSonicWeldInfo[15].VertexPairCount = 0;
		NPCSonicWeldInfo[15].VertexBuffer = 0;
		NPCSonicWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_DX) / 2);
		NPCSonicWeldInfo[14].ModelB = v4;
		NPCSonicWeldInfo[14].WeldType = 2;
		NPCSonicWeldInfo[14].VertIndexes = Sonic_UpperArmIndices_DX;
		NPCSonicWeldInfo[15].VertIndexes = 0;
	}

void Init_Sonic()
{
	HMODULE hm = GetModuleHandle(L"CHRMODELS_orig");
	NJS_OBJECT** SONIC_OBJECTS = (NJS_OBJECT**)GetProcAddress(hm, "___SONIC_OBJECTS");
	WriteJump((void*)0x007D0B50, InitSonicWeldInfo_mod);
	WriteJump((void*)0x007D14D0, InitSonicWeldInfo_mod);
}

__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
{
	HMODULE Hyper = GetModuleHandle(L"sadx-hyper-sonic");
	WriteCall((void*)0x4A1705, SetLSDColor);
	//Welding
	Init_Sonic();
	//Replace textures
	WriteData((NJS_TEXLIST**)0x55E65C, SSAura01);
	WriteData((NJS_TEXLIST**)0x55E751, SSAura01);
	WriteData((NJS_TEXLIST**)0x55E712, SSAura02);
	WriteData((NJS_TEXLIST**)0x55E7CD, SSWaterThing);
	WriteData((NJS_TEXLIST**)0x55F2B3, SSHomingTex1);
	WriteData((NJS_TEXLIST**)0x55F1D1, SSHomingTex1);
	WriteData((NJS_TEXLIST**)0x55F1DC, SSHomingTex2);
	WriteData((NJS_TEXLIST**)0x55F2BE, SSHomingTex2);
	WriteData((NJS_TEXLIST**)0x55F677, SSHomingTex2);
	WriteData((NJS_TEXLIST**)0x55F669, SSHomingTex3);
	SUPERSONIC_TEXLIST = SS_PVM;
	ReplacePVM("sonic", "GirlSonic");
	ReplacePVM("supersonic", "GirlSS");
	ReplacePVM("hypersonic", "GirlHS")
}
__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}