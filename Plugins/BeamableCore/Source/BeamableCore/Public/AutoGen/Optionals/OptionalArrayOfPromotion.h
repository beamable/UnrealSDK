#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Promotion.h"

#include "OptionalArrayOfPromotion.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfPromotionLibrary.MakeOptional", BeamOptionalType="TArray<UPromotion*>"))
struct BEAMABLECORE_API FOptionalArrayOfPromotion : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UPromotion*> Val;

	FOptionalArrayOfPromotion();

	explicit FOptionalArrayOfPromotion(TArray<UPromotion*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};