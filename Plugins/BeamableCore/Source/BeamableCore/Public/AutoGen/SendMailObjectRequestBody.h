
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalPlayerReward.h"
#include "AutoGen/Optionals/OptionalMailRewards.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalArrayOfAttachmentRequestBody.h"

#include "SendMailObjectRequestBody.generated.h"

UCLASS(BlueprintType)
class USendMailObjectRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Body")
	FOptionalString Body;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Expires")
	FOptionalString Expires;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Rewards")
	FOptionalPlayerReward PlayerRewards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Subject")
	FOptionalString Subject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rewards")
	FOptionalMailRewards Rewards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id")
	FOptionalInt64 Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sender Gamer Tag")
	int64 SenderGamerTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Category")
	FString Category;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Body Ref")
	FOptionalInt64 BodyRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Attachments")
	FOptionalArrayOfAttachmentRequestBody Attachments;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};