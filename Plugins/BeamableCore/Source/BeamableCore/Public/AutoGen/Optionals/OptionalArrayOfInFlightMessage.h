#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/InFlightMessage.h"

#include "OptionalArrayOfInFlightMessage.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfInFlightMessageLibrary.MakeOptional", BeamOptionalType="TArray<UInFlightMessage*>"))
struct BEAMABLECORE_API FOptionalArrayOfInFlightMessage : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UInFlightMessage*> Val;

	FOptionalArrayOfInFlightMessage();

	explicit FOptionalArrayOfInFlightMessage(TArray<UInFlightMessage*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};