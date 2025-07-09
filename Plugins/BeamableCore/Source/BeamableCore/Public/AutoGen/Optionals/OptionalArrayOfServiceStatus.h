#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ServiceStatus.h"

#include "OptionalArrayOfServiceStatus.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfServiceStatusLibrary.MakeOptional", BeamOptionalType="TArray<UServiceStatus*>"))
struct BEAMABLECORE_API FOptionalArrayOfServiceStatus : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UServiceStatus*> Val;

	FOptionalArrayOfServiceStatus();

	explicit FOptionalArrayOfServiceStatus(TArray<UServiceStatus*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};