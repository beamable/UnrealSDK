#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ItemCreateRequestBody.h"

#include "OptionalArrayOfItemCreateRequestBody.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfItemCreateRequestBodyLibrary.MakeOptional", BeamOptionalType="TArray<UItemCreateRequestBody*>"))
struct BEAMABLECORE_API FOptionalArrayOfItemCreateRequestBody : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UItemCreateRequestBody*> Val;

	FOptionalArrayOfItemCreateRequestBody();

	explicit FOptionalArrayOfItemCreateRequestBody(TArray<UItemCreateRequestBody*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};