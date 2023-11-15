#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ServiceDependencyReference.h"

#include "OptionalArrayOfServiceDependencyReference.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfServiceDependencyReferenceLibrary.MakeOptional", BeamOptionalType="TArray<UServiceDependencyReference*>"))
struct BEAMABLECORE_API FOptionalArrayOfServiceDependencyReference : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UServiceDependencyReference*> Val;

	FOptionalArrayOfServiceDependencyReference();

	explicit FOptionalArrayOfServiceDependencyReference(TArray<UServiceDependencyReference*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};