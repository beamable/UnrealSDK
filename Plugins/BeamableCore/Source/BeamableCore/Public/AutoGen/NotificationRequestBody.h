
#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/NotificationRequestData.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalArrayOfInt64.h"

#include "NotificationRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UNotificationRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Payload", Category="Beam")
	UNotificationRequestData* Payload;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Use Signal When Possible", Category="Beam")
	FOptionalBool bUseSignalWhenPossible;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Custom Channel Suffix", Category="Beam")
	FOptionalString CustomChannelSuffix;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Dbid", Category="Beam")
	FOptionalInt64 Dbid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Dbids", Category="Beam")
	FOptionalArrayOfInt64 Dbids;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};