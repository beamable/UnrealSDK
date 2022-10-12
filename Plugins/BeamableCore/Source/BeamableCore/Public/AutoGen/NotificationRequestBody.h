
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/NotificationRequestData.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalArrayOfInt64.h"

#include "NotificationRequestBody.generated.h"

UCLASS(BlueprintType)
class UNotificationRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Payload")
	UNotificationRequestData* Payload;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Custom Channel Suffix")
	FOptionalString CustomChannelSuffix;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Dbid")
	FOptionalInt64 Dbid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Use Signal When Possible")
	FOptionalBool bUseSignalWhenPossible;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Dbids")
	FOptionalArrayOfInt64 Dbids;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};