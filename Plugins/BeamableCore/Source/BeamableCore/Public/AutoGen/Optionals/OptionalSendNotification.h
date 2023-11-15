#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/SendNotification.h"

#include "OptionalSendNotification.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalSendNotificationLibrary.MakeOptional", BeamOptionalType="USendNotification*"))
struct BEAMABLECORE_API FOptionalSendNotification : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	USendNotification* Val;

	FOptionalSendNotification();

	explicit FOptionalSendNotification(USendNotification* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};