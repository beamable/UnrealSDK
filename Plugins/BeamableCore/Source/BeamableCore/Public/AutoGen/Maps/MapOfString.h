
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamMap.h"


#include "MapOfString.generated.h"

USTRUCT(BlueprintType)
struct FMapOfString : public FBeamMap
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FString> Values;

	FMapOfString();

	FMapOfString(const TMap<FString, FString>& Val);

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;

	virtual void BeamDeserializeElements(const TSharedPtr<FJsonObject>& Elements) override;
};