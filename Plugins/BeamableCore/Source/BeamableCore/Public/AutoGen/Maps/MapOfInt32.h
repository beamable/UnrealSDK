#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamMap.h"
#include "Serialization/BeamJsonUtils.h"

#include "MapOfInt32.generated.h"

USTRUCT(BlueprintType, Category="Beam|₢ServiceName₢|Wrappers|Maps")
struct BEAMABLECORE_API FMapOfInt32 : public FBeamMap
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TMap<FString, int32> Values;

	FMapOfInt32();

	FMapOfInt32(const TMap<FString, int32>& Val);

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;

	virtual void BeamDeserializeElements(const TSharedPtr<FJsonObject>& Elements) override;
};