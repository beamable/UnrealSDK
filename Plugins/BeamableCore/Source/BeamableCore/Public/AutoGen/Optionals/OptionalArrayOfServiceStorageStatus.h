#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ServiceStorageStatus.h"

#include "OptionalArrayOfServiceStorageStatus.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfServiceStorageStatusLibrary.MakeOptional", BeamOptionalType="TArray<UServiceStorageStatus*>"))
struct BEAMABLECORE_API FOptionalArrayOfServiceStorageStatus : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UServiceStorageStatus*> Val;

	FOptionalArrayOfServiceStorageStatus();

	explicit FOptionalArrayOfServiceStorageStatus(TArray<UServiceStorageStatus*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};