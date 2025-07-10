#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ServiceRegistration.h"

#include "OptionalArrayOfServiceRegistration.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfServiceRegistrationLibrary.MakeOptional", BeamOptionalType="TArray<UServiceRegistration*>"))
struct BEAMABLECORE_API FOptionalArrayOfServiceRegistration : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UServiceRegistration*> Val;

	FOptionalArrayOfServiceRegistration();

	explicit FOptionalArrayOfServiceRegistration(TArray<UServiceRegistration*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};