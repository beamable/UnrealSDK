
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"
#include "AutoGen/Optionals/OptionalPlayerReward.h"
#include "AutoGen/Optionals/OptionalArrayOfPlayerStatRequirement.h"
#include "AutoGen/Optionals/OptionalMapOfString.h"
#include "AutoGen/Optionals/OptionalArrayOfAnnouncementAttachment.h"

#include "AnnouncementContent.generated.h"

UCLASS(BlueprintType)
class UAnnouncementContent : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Body")
	FString Body;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Channel")
	FString Channel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start Date")
	FOptionalString StartDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tags")
	FOptionalArrayOfString Tags;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gift")
	FOptionalPlayerReward Gift;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stat Requirements")
	FOptionalArrayOfPlayerStatRequirement StatRequirements;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol")
	FString Symbol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Client Data")
	FOptionalMapOfString ClientData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="End Date")
	FOptionalString EndDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Title")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Attachments")
	FOptionalArrayOfAnnouncementAttachment Attachments;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Summary")
	FString Summary;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};