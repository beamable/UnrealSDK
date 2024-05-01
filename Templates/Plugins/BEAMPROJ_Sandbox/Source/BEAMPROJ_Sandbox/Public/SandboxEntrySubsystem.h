// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/BeamLevelSubsystem.h"

#include "SandboxEntrySubsystem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class BEAMPROJSANDBOX_API USandboxEntrySubsystem : public UBeamLevelSubsystem
{
	GENERATED_BODY()

	virtual FString GetSpecificLevelName() const override { return FString("Sandbox"); }

	// Do whatever here!!!!
};
