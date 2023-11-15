#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ServiceComponent.h"

#include "OptionalArrayOfServiceComponent.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfServiceComponentLibrary.MakeOptional", BeamOptionalType="TArray<UServiceComponent*>"))
struct BEAMABLECORE_API FOptionalArrayOfServiceComponent : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UServiceComponent*> Val;

	FOptionalArrayOfServiceComponent();

	explicit FOptionalArrayOfServiceComponent(TArray<UServiceComponent*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};