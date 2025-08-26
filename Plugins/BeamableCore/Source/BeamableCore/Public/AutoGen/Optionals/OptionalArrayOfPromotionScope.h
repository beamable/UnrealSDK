#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/PromotionScope.h"

#include "OptionalArrayOfPromotionScope.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfPromotionScopeLibrary.MakeOptional", BeamOptionalType="TArray<UPromotionScope*>"))
struct BEAMABLECORE_API FOptionalArrayOfPromotionScope : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UPromotionScope*> Val;

	FOptionalArrayOfPromotionScope();

	explicit FOptionalArrayOfPromotionScope(TArray<UPromotionScope*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};