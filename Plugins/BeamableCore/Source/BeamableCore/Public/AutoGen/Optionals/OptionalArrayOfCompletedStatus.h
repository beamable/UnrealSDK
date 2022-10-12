
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/CompletedStatus.h"

#include "OptionalArrayOfCompletedStatus.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalArrayOfCompletedStatusLibrary.MakeOptionalArrayOfCompletedStatus"))
struct FOptionalArrayOfCompletedStatus : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<UCompletedStatus*> Val;

	FOptionalArrayOfCompletedStatus();

	explicit FOptionalArrayOfCompletedStatus(TArray<UCompletedStatus*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};