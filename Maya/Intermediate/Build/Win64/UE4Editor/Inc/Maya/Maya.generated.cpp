// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Boilerplate C++ definitions for a single module.
	This is automatically generated by UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "Maya.h"
#include "Maya.generated.dep.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCode1Maya() {}
	void AManager::StaticRegisterNativesAManager()
	{
	}
	IMPLEMENT_CLASS(AManager, 2753437244);
	void AMayaGameMode::StaticRegisterNativesAMayaGameMode()
	{
	}
	IMPLEMENT_CLASS(AMayaGameMode, 1327354493);
	void APolygon::StaticRegisterNativesAPolygon()
	{
	}
	IMPLEMENT_CLASS(APolygon, 3784806056);
#if USE_COMPILED_IN_NATIVES
// Cross Module References
	ENGINE_API class UClass* Z_Construct_UClass_AActor();
	COREUOBJECT_API class UScriptStruct* Z_Construct_UScriptStruct_FRotator();
	COREUOBJECT_API class UScriptStruct* Z_Construct_UScriptStruct_FVector();
	ENGINE_API class UClass* Z_Construct_UClass_AGameMode();
	ENGINE_API class UClass* Z_Construct_UClass_UParticleSystem_NoRegister();

	MAYA_API class UClass* Z_Construct_UClass_AManager_NoRegister();
	MAYA_API class UClass* Z_Construct_UClass_AManager();
	MAYA_API class UClass* Z_Construct_UClass_AMayaGameMode_NoRegister();
	MAYA_API class UClass* Z_Construct_UClass_AMayaGameMode();
	MAYA_API class UClass* Z_Construct_UClass_APolygon_NoRegister();
	MAYA_API class UClass* Z_Construct_UClass_APolygon();
	MAYA_API class UPackage* Z_Construct_UPackage__Script_Maya();
	UClass* Z_Construct_UClass_AManager_NoRegister()
	{
		return AManager::StaticClass();
	}
	UClass* Z_Construct_UClass_AManager()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_AActor();
			Z_Construct_UPackage__Script_Maya();
			OuterClass = AManager::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20900080;


PRAGMA_DISABLE_DEPRECATION_WARNINGS
				UProperty* NewProp_SpawnRot = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("SpawnRot"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(SpawnRot, AManager), 0x0010000000010001, Z_Construct_UScriptStruct_FRotator());
				UProperty* NewProp_SpawnLoc = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("SpawnLoc"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(SpawnLoc, AManager), 0x0010000000010001, Z_Construct_UScriptStruct_FVector());
				UProperty* NewProp_polygonSubClass = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("polygonSubClass"), RF_Public|RF_Transient|RF_MarkAsNative) UClassProperty(CPP_PROPERTY_BASE(polygonSubClass, AManager), 0x0014000000010001, Z_Construct_UClass_APolygon_NoRegister(), UClass::StaticClass());
PRAGMA_ENABLE_DEPRECATION_WARNINGS
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("Manager.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("Manager.h"));
				MetaData->SetValue(NewProp_SpawnRot, TEXT("Category"), TEXT("Spawning Object"));
				MetaData->SetValue(NewProp_SpawnRot, TEXT("ModuleRelativePath"), TEXT("Manager.h"));
				MetaData->SetValue(NewProp_SpawnLoc, TEXT("Category"), TEXT("Spawning Object"));
				MetaData->SetValue(NewProp_SpawnLoc, TEXT("ModuleRelativePath"), TEXT("Manager.h"));
				MetaData->SetValue(NewProp_polygonSubClass, TEXT("Category"), TEXT("Spawn"));
				MetaData->SetValue(NewProp_polygonSubClass, TEXT("ModuleRelativePath"), TEXT("Manager.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AManager(Z_Construct_UClass_AManager, &AManager::StaticClass, TEXT("AManager"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AManager);
	UClass* Z_Construct_UClass_AMayaGameMode_NoRegister()
	{
		return AMayaGameMode::StaticClass();
	}
	UClass* Z_Construct_UClass_AMayaGameMode()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_AGameMode();
			Z_Construct_UPackage__Script_Maya();
			OuterClass = AMayaGameMode::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x2090028C;


				OuterClass->ClassConfigName = FName(TEXT("Game"));
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("HideCategories"), TEXT("Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation"));
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("MayaGameMode.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("MayaGameMode.h"));
				MetaData->SetValue(OuterClass, TEXT("ShowCategories"), TEXT("Input|MouseInput Input|TouchInput"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AMayaGameMode(Z_Construct_UClass_AMayaGameMode, &AMayaGameMode::StaticClass, TEXT("AMayaGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMayaGameMode);
	UClass* Z_Construct_UClass_APolygon_NoRegister()
	{
		return APolygon::StaticClass();
	}
	UClass* Z_Construct_UClass_APolygon()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_AActor();
			Z_Construct_UPackage__Script_Maya();
			OuterClass = APolygon::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20900080;


PRAGMA_DISABLE_DEPRECATION_WARNINGS
				UProperty* NewProp_lineType = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("lineType"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(CPP_PROPERTY_BASE(lineType, APolygon), 0x0010000000010001, Z_Construct_UClass_UParticleSystem_NoRegister());
				UProperty* NewProp_SpawnRot = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("SpawnRot"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(SpawnRot, APolygon), 0x0010000000010001, Z_Construct_UScriptStruct_FRotator());
				UProperty* NewProp_SpawnLoc = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("SpawnLoc"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(SpawnLoc, APolygon), 0x0010000000010001, Z_Construct_UScriptStruct_FVector());
PRAGMA_ENABLE_DEPRECATION_WARNINGS
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("Polygon.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("Polygon.h"));
				MetaData->SetValue(OuterClass, TEXT("ObjectInitializerConstructorDeclared"), TEXT(""));
				MetaData->SetValue(NewProp_lineType, TEXT("Category"), TEXT("Beam"));
				MetaData->SetValue(NewProp_lineType, TEXT("ModuleRelativePath"), TEXT("Polygon.h"));
				MetaData->SetValue(NewProp_SpawnRot, TEXT("Category"), TEXT("Spawning Object"));
				MetaData->SetValue(NewProp_SpawnRot, TEXT("ModuleRelativePath"), TEXT("Polygon.h"));
				MetaData->SetValue(NewProp_SpawnLoc, TEXT("Category"), TEXT("Spawning Object"));
				MetaData->SetValue(NewProp_SpawnLoc, TEXT("ModuleRelativePath"), TEXT("Polygon.h"));
				MetaData->SetValue(NewProp_SpawnLoc, TEXT("ToolTip"), TEXT("-- Spawn --"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_APolygon(Z_Construct_UClass_APolygon, &APolygon::StaticClass, TEXT("APolygon"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(APolygon);
	UPackage* Z_Construct_UPackage__Script_Maya()
	{
		static UPackage* ReturnPackage = NULL;
		if (!ReturnPackage)
		{
			ReturnPackage = CastChecked<UPackage>(StaticFindObjectFast(UPackage::StaticClass(), NULL, FName(TEXT("/Script/Maya")), false, false));
			ReturnPackage->SetPackageFlags(PKG_CompiledIn | 0x00000000);
			FGuid Guid;
			Guid.A = 0x27028449;
			Guid.B = 0xE8657FE9;
			Guid.C = 0x00000000;
			Guid.D = 0x00000000;
			ReturnPackage->SetGuid(Guid);

		}
		return ReturnPackage;
	}
#endif

PRAGMA_ENABLE_DEPRECATION_WARNINGS
