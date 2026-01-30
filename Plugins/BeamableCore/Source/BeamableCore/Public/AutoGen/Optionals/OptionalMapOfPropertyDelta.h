#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/PropertyDelta.h"

#include "OptionalMapOfPropertyDelta.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalMapOfPropertyDeltaLibrary.MakeOptional", BeamOptionalType="TMap<FString, UPropertyDelta*>"))
struct BEAMABLECORE_API FOptionalMapOfPropertyDelta : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<FString, UPropertyDelta*> Val;

	FOptionalMapOfPropertyDelta();

	explicit FOptionalMapOfPropertyDelta(TMap<FString, UPropertyDelta*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};