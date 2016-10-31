// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef MAYA_MayaGameMode_generated_h
#error "MayaGameMode.generated.h already included, missing '#pragma once' in MayaGameMode.h"
#endif
#define MAYA_MayaGameMode_generated_h

#define Maya_Source_Maya_MayaGameMode_h_14_RPC_WRAPPERS
#define Maya_Source_Maya_MayaGameMode_h_14_RPC_WRAPPERS_NO_PURE_DECLS
#define Maya_Source_Maya_MayaGameMode_h_14_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesAMayaGameMode(); \
	friend MAYA_API class UClass* Z_Construct_UClass_AMayaGameMode(); \
	public: \
	DECLARE_CLASS(AMayaGameMode, AGameMode, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), 0, TEXT("/Script/Maya"), NO_API) \
	DECLARE_SERIALIZER(AMayaGameMode) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define Maya_Source_Maya_MayaGameMode_h_14_INCLASS \
	private: \
	static void StaticRegisterNativesAMayaGameMode(); \
	friend MAYA_API class UClass* Z_Construct_UClass_AMayaGameMode(); \
	public: \
	DECLARE_CLASS(AMayaGameMode, AGameMode, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), 0, TEXT("/Script/Maya"), NO_API) \
	DECLARE_SERIALIZER(AMayaGameMode) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define Maya_Source_Maya_MayaGameMode_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AMayaGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AMayaGameMode) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMayaGameMode); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMayaGameMode); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AMayaGameMode(AMayaGameMode&&); \
	NO_API AMayaGameMode(const AMayaGameMode&); \
public:


#define Maya_Source_Maya_MayaGameMode_h_14_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AMayaGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AMayaGameMode(AMayaGameMode&&); \
	NO_API AMayaGameMode(const AMayaGameMode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMayaGameMode); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMayaGameMode); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AMayaGameMode)


#define Maya_Source_Maya_MayaGameMode_h_11_PROLOG
#define Maya_Source_Maya_MayaGameMode_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Maya_Source_Maya_MayaGameMode_h_14_RPC_WRAPPERS \
	Maya_Source_Maya_MayaGameMode_h_14_INCLASS \
	Maya_Source_Maya_MayaGameMode_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Maya_Source_Maya_MayaGameMode_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Maya_Source_Maya_MayaGameMode_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	Maya_Source_Maya_MayaGameMode_h_14_INCLASS_NO_PURE_DECLS \
	Maya_Source_Maya_MayaGameMode_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Maya_Source_Maya_MayaGameMode_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
