#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamPromotableType.h"

#include "OptionalArrayOfBeamPromotableType.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamPromotableTypeLibrary.MakeOptional", BeamOptionalType="TArray<EBeamPromotableType>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamPromotableType : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<EBeamPromotableType> Val;

	FOptionalArrayOfBeamPromotableType();

	explicit FOptionalArrayOfBeamPromotableType(TArray<EBeamPromotableType> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};