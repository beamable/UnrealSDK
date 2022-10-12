
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "ListTokenResponseItem.generated.h"

UCLASS(BlueprintType)
class UListTokenResponseItem : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Token")
	FString Token;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Platform")
	FString Platform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Device")
	FString Device;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created")
	FString Created;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};