// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamJsonUtils.h"

#include "BeamOptionalTypes.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.BeamOptionalTypesLibrary.MakeOptionalInt"))
struct FOptionalInt : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int Val;

	FOptionalInt();

	explicit FOptionalInt(int Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.BeamOptionalTypesLibrary.MakeOptionalString"))
struct FOptionalString : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString Val;

	FOptionalString();

	explicit FOptionalString(FString Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};