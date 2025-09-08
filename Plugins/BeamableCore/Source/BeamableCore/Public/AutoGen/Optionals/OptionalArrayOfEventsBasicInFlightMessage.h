#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/EventsBasicInFlightMessage.h"

#include "OptionalArrayOfEventsBasicInFlightMessage.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfEventsBasicInFlightMessageLibrary.MakeOptional", BeamOptionalType="TArray<UEventsBasicInFlightMessage*>"))
struct BEAMABLECORE_API FOptionalArrayOfEventsBasicInFlightMessage : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UEventsBasicInFlightMessage*> Val;

	FOptionalArrayOfEventsBasicInFlightMessage();

	explicit FOptionalArrayOfEventsBasicInFlightMessage(TArray<UEventsBasicInFlightMessage*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};