#include "pch.h"
#include "sstextlist.h"

#define ReplacePVM(a, b) helperFunctions.ReplaceFile("system\\" a ".PVM", "system\\" b ".PVM");
NJS_MATERIAL* TemporaryMaterialArray[] = { nullptr };

void Tornado_init(const HelperFunctions& helperFunctions);

DataPointer(NJS_OBJECT, SonicPointingHand_Object, 0x2DD8708);

//Light Dash Aura for DX, colors in Alpha, Red, Green, Blue
void __cdecl SetLSDColor()
{
	SetMaterialAndSpriteColor_Float(0.8f, 0.7f, 0.1f, 0.65f);
}

//Light Dash Aura for DC conversion
void __cdecl Sonic_DisplayLightDashModel_mod(EntityData1* data1, EntityData2* data2_pp, CharObj2* data2)
{
	int v3; // eax
	__int16 v4; // t1
	double v5; // st7
	float v6; // ST28_4
	double v7; // st7
	NJS_ACTION v8; // [esp+4h] [ebp-18h]
	NJS_ARGB a1; // [esp+Ch] [ebp-10h]

	if (!MissedFrames)
	{
		v3 = (unsigned __int16)data2->AnimationThing.Index;
		v8.object = SONIC_OBJECTS[54];
		if (data2->AnimationThing.State == 2)
		{
			v4 = data2->AnimationThing.LastIndex;
			v8.motion = data2->AnimationThing.action->motion;
		}
		else
		{
			v8.motion = data2->AnimationThing.AnimData[v3].Animation->motion;
		}
		v5 = (double)(LevelFrameCount & 0x7F);
		if (v5 >= 64.0)
		{
			v5 = 128.0 - v5;
		}
		v6 = v5 * 0.015625;
		njPushMatrixEx();
		njControl3D(NJD_CONTROL_3D_CONSTANT_MATERIAL | NJD_CONTROL_3D_ENABLE_ALPHA | NJD_CONTROL_3D_CONSTANT_ATTR);
		njColorBlendingMode(0, NJD_COLOR_BLENDING_SRCALPHA);
		njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_ONE);
		v7 = v6 * 0.1;
		a1.r = 0.7;
		a1.a = 0.8;
		a1.g = 0.1 - v7;
		a1.b = 0.65 - v7;
		SetMaterialAndSpriteColor(&a1);
		njAction_Queue_407FC0(&v8, data2->AnimationThing.Frame, 0);
		njScale(0, 1.05, 1.05, 1.05);
		njAction_Queue_407FC0(&v8, data2->AnimationThing.Frame, 0);
		njScale(0, 1.05, 1.05, 1.05);
		njAction_Queue_407FC0(&v8, data2->AnimationThing.Frame, 0);
		njColorBlendingMode(0, NJD_COLOR_BLENDING_SRCALPHA);
		njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);
		njPopMatrixEx();
	}
}

void PointingFinger_Init(const HelperFunctions& helperFunctions) {
	ModelInfo* mdl = new ModelInfo(helperFunctions.GetReplaceablePath("system\\SONIC_POINTINGHAND.sa1mdl"));

	if (mdl->getformat() == ModelFormat_Basic) {
		SonicPointingHand_Object = *mdl->getmodel();
	}
}

extern "C"
{
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		// Replace the light speed dash aura color
		WriteCall((void*)0x4A1705, SetLSDColor);
		WriteJump((void*)0x4A1630, Sonic_DisplayLightDashModel_mod);

		// Replace the pointing finger model that's used in cutscenes
		PointingFinger_Init(helperFunctions);

		// Replace Sonic on the Tornado
		Tornado_init(helperFunctions);

		//To make Super form work
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

		//Replace textures
		ReplacePVM("sonic", "GirlSonic");
		ReplacePVM("supersonic", "GirlSS");
		ReplacePVM("hypersonic", "GirlHS");
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}