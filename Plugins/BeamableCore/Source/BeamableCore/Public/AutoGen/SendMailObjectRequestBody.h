#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalPlayerReward.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMailRewards.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfAttachmentRequestBody.h"

#include "SendMailObjectRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API USendMailObjectRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sender Gamer Tag", Category="Beam")
	int64 SenderGamerTag = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Category", Category="Beam")
	FString Category = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Body", Category="Beam")
	FOptionalString Body = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Expires", Category="Beam")
	FOptionalString Expires = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Rewards", Category="Beam")
	FOptionalPlayerReward PlayerRewards = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Subject", Category="Beam")
	FOptionalString Subject = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rewards", Category="Beam")
	FOptionalMailRewards Rewards = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FOptionalInt64 Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Body Ref", Category="Beam")
	FOptionalInt64 BodyRef = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Attachments", Category="Beam")
	FOptionalArrayOfAttachmentRequestBody Attachments = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};