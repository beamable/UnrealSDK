#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/PartyInvitation.h"

#include "OptionalArrayOfPartyInvitation.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfPartyInvitationLibrary.MakeOptional", BeamOptionalType="TArray<UPartyInvitation*>"))
struct BEAMABLECORE_API FOptionalArrayOfPartyInvitation : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UPartyInvitation*> Val;

	FOptionalArrayOfPartyInvitation();

	explicit FOptionalArrayOfPartyInvitation(TArray<UPartyInvitation*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};