#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamArray.h"
#include "Serialization/BeamJsonUtils.h"

#include "ArrayOfInt32.generated.h"
		
USTRUCT(BlueprintType, Category="Beam|₢ServiceName₢|Wrappers|Arrays")
struct BEAMABLECORE_API FArrayOfInt32 : public FBeamArray
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TArray<int32> Values;

	FArrayOfInt32();

	explicit FArrayOfInt32(const TArray<int32>& Values);

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;

	virtual void BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements) override;
};
