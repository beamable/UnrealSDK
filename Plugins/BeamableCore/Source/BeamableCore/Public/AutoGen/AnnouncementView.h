#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"
#include "BeamableCore/Public/AutoGen/ClientDataEntry.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalPlayerReward.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/AnnouncementAttachment.h"

#include "AnnouncementView.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UAnnouncementView : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is Claimed", Category="Beam")
	bool bIsClaimed = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is Deleted", Category="Beam")
	bool bIsDeleted = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is Read", Category="Beam")
	bool bIsRead = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Body", Category="Beam")
	FString Body = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Channel", Category="Beam")
	FString Channel = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FString Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Title", Category="Beam")
	FString Title = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Summary", Category="Beam")
	FString Summary = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Client Data List", Category="Beam")
	TArray<UClientDataEntry*> ClientDataList = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Attachments", Category="Beam")
	TArray<UAnnouncementAttachment*> Attachments = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="End Date", Category="Beam")
	FOptionalString EndDate = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gift", Category="Beam")
	FOptionalPlayerReward Gift = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Seconds Remaining", Category="Beam")
	FOptionalInt64 SecondsRemaining = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start Date", Category="Beam")
	FOptionalString StartDate = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tags", Category="Beam")
	FOptionalArrayOfString Tags = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};