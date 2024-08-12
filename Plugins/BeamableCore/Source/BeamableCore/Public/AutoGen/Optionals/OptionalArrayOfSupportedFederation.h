#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/SupportedFederation.h"

#include "OptionalArrayOfSupportedFederation.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfSupportedFederationLibrary.MakeOptional", BeamOptionalType="TArray<USupportedFederation*>"))
struct BEAMABLECORE_API FOptionalArrayOfSupportedFederation : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<USupportedFederation*> Val;

	FOptionalArrayOfSupportedFederation();

	explicit FOptionalArrayOfSupportedFederation(TArray<USupportedFederation*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};