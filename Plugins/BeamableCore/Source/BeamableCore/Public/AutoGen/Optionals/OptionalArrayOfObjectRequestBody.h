#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ObjectRequestBody.h"

#include "OptionalArrayOfObjectRequestBody.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfObjectRequestBodyLibrary.MakeOptional", BeamOptionalType="TArray<UObjectRequestBody*>"))
struct BEAMABLECORE_API FOptionalArrayOfObjectRequestBody : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UObjectRequestBody*> Val;

	FOptionalArrayOfObjectRequestBody();

	explicit FOptionalArrayOfObjectRequestBody(TArray<UObjectRequestBody*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};