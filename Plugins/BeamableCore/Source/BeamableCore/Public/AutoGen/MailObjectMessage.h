
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/Optionals/OptionalPlayerReward.h"
#include "AutoGen/Optionals/OptionalMailRewards.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Attachment.h"

#include "MailObjectMessage.generated.h"

UCLASS(BlueprintType)
class UMailObjectMessage : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Body")
	FOptionalString Body;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Expires")
	FOptionalInt32 Expires;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Rewards")
	FOptionalPlayerReward PlayerRewards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Receiver Gamer Tag")
	int64 ReceiverGamerTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Subject")
	FOptionalString Subject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="State")
	FString State;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rewards")
	FOptionalMailRewards Rewards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id")
	int64 Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sender Gamer Tag")
	int64 SenderGamerTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sent")
	int64 Sent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Category")
	FString Category;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Body Ref")
	FOptionalInt64 BodyRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Attachments")
	TArray<UAttachment*> Attachments;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Claimed Time Ms")
	FOptionalInt64 ClaimedTimeMs;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};