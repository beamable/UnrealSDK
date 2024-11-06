// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SemanticTypes/BeamCid.h"
#include "SemanticTypes/BeamPid.h"

#include "BeamRealmHandle.generated.h"


USTRUCT(BlueprintType)
struct FBeamRealmHandle
{
	GENERATED_BODY()

	/**
	 * @brief The CustomerId that owns the given realm.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Beam")
	FBeamCid Cid;

	/**
	 * @brief The RealmId, AKA Project Id, that identifies this realm.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Beam")
	FBeamPid Pid;

	friend bool operator==(const FBeamRealmHandle& Lhs, const FBeamRealmHandle& RHS)
	{
		return Lhs.Cid == RHS.Cid
			&& Lhs.Pid == RHS.Pid;
	}

	friend bool operator!=(const FBeamRealmHandle& Lhs, const FBeamRealmHandle& RHS)
	{
		return !(Lhs == RHS);
	}

	bool IsValid() { return !Cid.AsString.IsEmpty(); }
};
