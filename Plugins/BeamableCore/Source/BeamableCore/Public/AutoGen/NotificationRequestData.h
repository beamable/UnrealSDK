#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfString.h"

#include "NotificationRequestData.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UNotificationRequestData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Channel", Category="Beam")
	FOptionalString Channel = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Message Key", Category="Beam")
	FOptionalString MessageKey = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Context", Category="Beam")
	FOptionalString Context = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Shard", Category="Beam")
	FOptionalString Shard = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Message Full", Category="Beam")
	FOptionalString MessageFull = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Message Params", Category="Beam")
	FOptionalArrayOfString MessageParams = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Meta", Category="Beam")
	FOptionalMapOfString Meta = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};