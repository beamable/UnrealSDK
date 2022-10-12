
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "InFlightMessage.generated.h"

UCLASS(BlueprintType)
class UInFlightMessage : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Method")
	FString Method;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Body")
	FString Body;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Path")
	FString Path;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag")
	FOptionalInt64 GamerTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Shard")
	FOptionalString Shard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service")
	FString Service;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id")
	FString Id;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};