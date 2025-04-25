#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamArray.h"
#include "BeamableCore/Public/AutoGen/LocalizedValue.h"

#include "ArrayOfLocalizedValue.generated.h"
		
USTRUCT(BlueprintType, Category="Beam|₢ServiceName₢|Wrappers|Arrays")
struct BEAMABLECORE_API FArrayOfLocalizedValue : public FBeamArray
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TArray<ULocalizedValue*> Values;

	FArrayOfLocalizedValue();

	explicit FArrayOfLocalizedValue(const TArray<ULocalizedValue*>& Values);

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;

	virtual void BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements) override;
};
