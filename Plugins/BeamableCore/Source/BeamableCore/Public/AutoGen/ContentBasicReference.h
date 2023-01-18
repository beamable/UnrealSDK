
#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Enums/ContentType.h"

#include "ContentBasicReference.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UContentBasicReference : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Prefix", Category="Beam")
	FString ContentPrefix;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Visibility", Category="Beam")
	FString Visibility;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type", Category="Beam")
	EContentType Type;

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};