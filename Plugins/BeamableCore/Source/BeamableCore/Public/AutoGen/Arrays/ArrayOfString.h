#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamArray.h"
#include "Serialization/BeamJsonUtils.h"

#include "ArrayOfString.generated.h"
		
USTRUCT(BlueprintType, Category="Beam|₢ServiceName₢|Wrappers|Arrays")
struct BEAMABLECORE_API FArrayOfString : public FBeamArray
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TArray<FString> Values;

	FArrayOfString();

	explicit FArrayOfString(const TArray<FString>& Values);

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;

	virtual void BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements) override;
};
