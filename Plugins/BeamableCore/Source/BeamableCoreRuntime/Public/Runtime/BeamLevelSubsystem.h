// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BeamLevelSubsystem.generated.h"

/**
 * Just a helper abstract class that ensures its subclasses only exist in specific levels.
 */
UCLASS(BlueprintType, Abstract)
class BEAMABLECORERUNTIME_API UBeamLevelSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:
	/**
	 * Should return the name of the Level that this subsystem must exist in.
	 */
	virtual FString GetSpecificLevelName() const
	{
		checkf(false, TEXT("MUST IMPLEMENT THIS FUNCTION IN YOUR SUBCLASS"));
		return FString();
	};

	/**
	 * Returns true if the World we are currently loaded ends with the Level name defined by GetSpecificLevelName.
	 *
	 * In PIE, there's a prefix added so that the level name becomes something like this: UEDPIE_0_Sandbox --- so we check via EndsWith.
	 */
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override
	{
		if (!Super::ShouldCreateSubsystem(Outer))
			return false;

		// In PIE, there's a prefix added so that the level name becomes something like this: UEDPIE_0_Sandbox
		const auto World = Cast<UWorld>(Outer);
		const auto MapName = World->GetMapName();
		const auto SpecificMapName = GetSpecificLevelName();
		const auto IsMapEqual = MapName.EndsWith(SpecificMapName);
		return IsMapEqual;
	}

	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		Super::Initialize(Collection);
		UE_LOG(LogTemp, Warning, TEXT("Initializing Level Subsystem. LEVEL=%s, PREFIXED_LEVEL_NAME=%s"), *GetSpecificLevelName(), *GetWorld()->GetMapName());
	}
};
