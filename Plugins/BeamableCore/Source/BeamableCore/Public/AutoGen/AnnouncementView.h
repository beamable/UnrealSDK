
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"
#include "AutoGen/ClientDataEntry.h"
#include "AutoGen/Optionals/OptionalPlayerReward.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/AnnouncementAttachment.h"

#include "AnnouncementView.generated.h"

UCLASS(BlueprintType)
class UAnnouncementView : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Body")
	FString Body;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is Claimed")
	bool bIsClaimed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Channel")
	FString Channel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="End Date")
	FOptionalString EndDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tags")
	FOptionalArrayOfString Tags;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Client Data List")
	TArray<UClientDataEntry*> ClientDataList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gift")
	FOptionalPlayerReward Gift;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Seconds Remaining")
	FOptionalInt64 SecondsRemaining;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is Deleted")
	bool bIsDeleted;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is Read")
	bool bIsRead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Title")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start Date")
	FOptionalString StartDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Attachments")
	TArray<UAnnouncementAttachment*> Attachments;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Summary")
	FString Summary;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};