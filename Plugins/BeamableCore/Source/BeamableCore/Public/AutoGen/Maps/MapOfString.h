#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamMap.h"
#include "Serialization/BeamJsonUtils.h"

#include "MapOfString.generated.h"

USTRUCT(BlueprintType, Category="Beam|₢ServiceName₢|Wrappers|Maps")
struct BEAMABLECORE_API FMapOfString : public FBeamMap
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TMap<FString, FString> Values;

	FMapOfString();

	FMapOfString(const TMap<FString, FString>& Val);

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;

	virtual void BeamDeserializeElements(const TSharedPtr<FJsonObject>& Elements) override;
};