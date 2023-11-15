#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/CompletedStatus.h"

#include "OptionalArrayOfCompletedStatus.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfCompletedStatusLibrary.MakeOptional", BeamOptionalType="TArray<UCompletedStatus*>"))
struct BEAMABLECORE_API FOptionalArrayOfCompletedStatus : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UCompletedStatus*> Val;

	FOptionalArrayOfCompletedStatus();

	explicit FOptionalArrayOfCompletedStatus(TArray<UCompletedStatus*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};