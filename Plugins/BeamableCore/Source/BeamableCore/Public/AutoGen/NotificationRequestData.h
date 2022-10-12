
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalMapOfString.h"

#include "NotificationRequestData.generated.h"

UCLASS(BlueprintType)
class UNotificationRequestData : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Message Params")
	FOptionalArrayOfString MessageParams;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Channel")
	FOptionalString Channel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Message Key")
	FOptionalString MessageKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Context")
	FOptionalString Context;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Shard")
	FOptionalString Shard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Meta")
	FOptionalMapOfString Meta;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Message Full")
	FOptionalString MessageFull;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};