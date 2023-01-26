// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Arrays/ArrayOfString.h"
#include "AutoGen/Maps/MapOfString.h"
#include "AutoGen/Optionals/OptionalArrayOfBeamPid.h"
#include "AutoGen/Optionals/OptionalArrayOfInt32.h"
#include "AutoGen/Optionals/OptionalBeamCid.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalMapOfInt64.h"
#include "UObject/Interface.h"
#include "Content/BeamContentObject.h"

#include "MockBeamContentObject.generated.h"


UCLASS(BlueprintType, Blueprintable)
class UMockBeamContentObject : public UBeamContentObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBeamCid BeamCid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBeamCid> ArrayOfBeamCid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FBeamCid> MapOfBeamCid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> ArrayOfString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<uint8> ArrayOfU8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FString> MapOfString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, uint8> MapOfU8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FArrayOfString BeamArrayOfString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMapOfString BeamMapOfString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FArrayOfString> ArrayOfArrayOfString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMapOfString> ArrayOfMapOfString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FArrayOfString> MapOfArrayOfString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FMapOfString> MapOfMapOfString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOptionalBool BeamOptionalBool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOptionalArrayOfInt32 BeamOptionalArrayOfInt32;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOptionalMapOfInt64 BeamOptionalMapOfInt64;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOptionalBeamCid BeamOptionalBeamCid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOptionalArrayOfBeamPid BeamOptionalArrayOfBeamPid;
	
};

BEGIN_DEFINE_SPEC(FBeamContentObjectSpec, "BeamableUnreal.ContentObject", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
UMockBeamContentObject* ContentObject;
END_DEFINE_SPEC(FBeamContentObjectSpec)
