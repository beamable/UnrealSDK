// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalCatalog.h"
#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/Optionals/OptionalLeaderboardCohortSettings.h"
#include "BeamBackend/ReplacementTypes/BeamClientPermission.h"
#include "Content/BeamContentObject.h"
#include "BeamLeaderboardContent.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamLeaderboardContent : public UBeamContentObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void GetContentType_UBeamLeaderboardContent(FString& Result);

	/**
	 * Allow the clients to modify they own entries in the leaderboard
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Client Permission")
	FBeamClientPermission permissions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOptionalBool partitioned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOptionalInt32 max_entries;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOptionalLeaderboardCohortSettings cohortSettings;
};


DEFINE_CONTENT_TYPE_NAME(UBeamLeaderboardContent, "leaderboards")
