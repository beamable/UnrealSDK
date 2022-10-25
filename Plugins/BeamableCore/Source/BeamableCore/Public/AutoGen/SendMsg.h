
#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalSendNotification.h"
#include "AutoGen/Optionals/OptionalMapOfString.h"

#include "SendMsg.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USendMsg : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="To", Category="Beam")
	TArray<int64> To;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Notification", Category="Beam")
	FOptionalSendNotification Notification;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Data", Category="Beam")
	FOptionalMapOfString Data;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};