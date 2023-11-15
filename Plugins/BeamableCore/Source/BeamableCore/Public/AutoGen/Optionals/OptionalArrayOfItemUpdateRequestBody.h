#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ItemUpdateRequestBody.h"

#include "OptionalArrayOfItemUpdateRequestBody.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfItemUpdateRequestBodyLibrary.MakeOptional", BeamOptionalType="TArray<UItemUpdateRequestBody*>"))
struct BEAMABLECORE_API FOptionalArrayOfItemUpdateRequestBody : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UItemUpdateRequestBody*> Val;

	FOptionalArrayOfItemUpdateRequestBody();

	explicit FOptionalArrayOfItemUpdateRequestBody(TArray<UItemUpdateRequestBody*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};