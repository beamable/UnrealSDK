#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/GroupUsersObjectInFlightMessage.h"

#include "OptionalArrayOfGroupUsersObjectInFlightMessage.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfGroupUsersObjectInFlightMessageLibrary.MakeOptional", BeamOptionalType="TArray<UGroupUsersObjectInFlightMessage*>"))
struct BEAMABLECORE_API FOptionalArrayOfGroupUsersObjectInFlightMessage : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UGroupUsersObjectInFlightMessage*> Val;

	FOptionalArrayOfGroupUsersObjectInFlightMessage();

	explicit FOptionalArrayOfGroupUsersObjectInFlightMessage(TArray<UGroupUsersObjectInFlightMessage*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};