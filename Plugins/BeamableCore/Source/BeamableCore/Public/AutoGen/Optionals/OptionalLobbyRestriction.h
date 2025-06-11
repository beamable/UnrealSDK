#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamLobbyRestriction.h"

#include "OptionalLobbyRestriction.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalLobbyRestrictionLibrary.MakeOptional", BeamOptionalType="EBeamLobbyRestriction"))
struct BEAMABLECORE_API FOptionalLobbyRestriction : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EBeamLobbyRestriction Val;

	FOptionalLobbyRestriction();

	explicit FOptionalLobbyRestriction(EBeamLobbyRestriction Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};