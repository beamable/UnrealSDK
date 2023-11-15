#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ServiceStorageReference.h"

#include "OptionalArrayOfServiceStorageReference.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfServiceStorageReferenceLibrary.MakeOptional", BeamOptionalType="TArray<UServiceStorageReference*>"))
struct BEAMABLECORE_API FOptionalArrayOfServiceStorageReference : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UServiceStorageReference*> Val;

	FOptionalArrayOfServiceStorageReference();

	explicit FOptionalArrayOfServiceStorageReference(TArray<UServiceStorageReference*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};