#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ItemDeleteRequestBody.h"

#include "OptionalArrayOfItemDeleteRequestBody.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfItemDeleteRequestBodyLibrary.MakeOptional", BeamOptionalType="TArray<UItemDeleteRequestBody*>"))
struct BEAMABLECORE_API FOptionalArrayOfItemDeleteRequestBody : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UItemDeleteRequestBody*> Val;

	FOptionalArrayOfItemDeleteRequestBody();

	explicit FOptionalArrayOfItemDeleteRequestBody(TArray<UItemDeleteRequestBody*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};