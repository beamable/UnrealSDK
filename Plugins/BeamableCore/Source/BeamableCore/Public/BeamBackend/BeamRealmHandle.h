// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BeamRealmHandle.generated.h"


USTRUCT(BlueprintType)
struct FBeamRealmHandle
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString Cid;

	UPROPERTY(BlueprintReadOnly)
	FString Pid;

	friend bool operator==(const FBeamRealmHandle& Lhs, const FBeamRealmHandle& RHS)
	{
		return Lhs.Cid == RHS.Cid
			&& Lhs.Pid == RHS.Pid;
	}

	friend bool operator!=(const FBeamRealmHandle& Lhs, const FBeamRealmHandle& RHS)
	{
		return !(Lhs == RHS);
	}
};