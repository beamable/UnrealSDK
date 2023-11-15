#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Team.h"

#include "OptionalArrayOfTeam.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfTeamLibrary.MakeOptional", BeamOptionalType="TArray<UTeam*>"))
struct BEAMABLECORE_API FOptionalArrayOfTeam : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UTeam*> Val;

	FOptionalArrayOfTeam();

	explicit FOptionalArrayOfTeam(TArray<UTeam*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};