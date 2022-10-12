
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"

#include "PromoteRealmRequestBody.generated.h"

UCLASS(BlueprintType)
class UPromoteRealmRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Source Pid")
	FString SourcePid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Promotions")
	FOptionalArrayOfString Promotions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Manifest Ids")
	FOptionalArrayOfString ContentManifestIds;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};