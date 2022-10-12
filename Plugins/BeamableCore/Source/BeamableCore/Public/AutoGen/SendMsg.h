
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalSendNotification.h"
#include "AutoGen/Optionals/OptionalMapOfString.h"

#include "SendMsg.generated.h"

UCLASS(BlueprintType)
class USendMsg : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="To")
	TArray<int64> To;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Notification")
	FOptionalSendNotification Notification;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Data")
	FOptionalMapOfString Data;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};