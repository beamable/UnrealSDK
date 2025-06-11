#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "InFlightMessage.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UInFlightMessage : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Method", Category="Beam")
	FString Method = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Body", Category="Beam")
	FString Body = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Path", Category="Beam")
	FString Path = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service", Category="Beam")
	FString Service = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FString Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Limit Failure Retries", Category="Beam")
	FOptionalBool bLimitFailureRetries = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag", Category="Beam")
	FOptionalInt64 GamerTag = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Shard", Category="Beam")
	FOptionalString Shard = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};