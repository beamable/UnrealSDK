#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/LeaderboardCohortSettings.h"

#include "OptionalLeaderboardCohortSettings.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalLeaderboardCohortSettingsLibrary.MakeOptional", BeamOptionalType="ULeaderboardCohortSettings*"))
struct BEAMABLECORE_API FOptionalLeaderboardCohortSettings : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	ULeaderboardCohortSettings* Val;

	FOptionalLeaderboardCohortSettings();

	explicit FOptionalLeaderboardCohortSettings(ULeaderboardCohortSettings* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};