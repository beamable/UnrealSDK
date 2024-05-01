// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BeamableUnrealGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BEAMABLEUNREAL_API ABeamableUnrealGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override
	{
		FString ServerOrClient = GetGameInstance()->IsDedicatedServerInstance() ? TEXT("server") : TEXT("client");
		UE_LOG(LogTemp, Display, TEXT("Preparing BEAMPROJ for %s."), *ServerOrClient);

		TArray<FName> Modules;
		FModuleManager::Get().FindModules(TEXT("BEAMPROJ*"), Modules);

		if (Modules.Num() <= 0)
		{
			UE_LOG(LogTemp, Error, TEXT("Found no loaded BEAMPROJ module for %s."), *ServerOrClient);
		}
	}
};
