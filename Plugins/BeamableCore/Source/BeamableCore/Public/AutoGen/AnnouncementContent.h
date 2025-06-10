#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalPlayerReward.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfPlayerStatRequirement.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfAnnouncementAttachment.h"

#include "AnnouncementContent.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UAnnouncementContent : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Body", Category="Beam")
	FString Body = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Channel", Category="Beam")
	FString Channel = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol", Category="Beam")
	FString Symbol = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Title", Category="Beam")
	FString Title = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Summary", Category="Beam")
	FString Summary = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start Date", Category="Beam")
	FOptionalString StartDate = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gift", Category="Beam")
	FOptionalPlayerReward Gift = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="End Date", Category="Beam")
	FOptionalString EndDate = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tags", Category="Beam")
	FOptionalArrayOfString Tags = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stat Requirements", Category="Beam")
	FOptionalArrayOfPlayerStatRequirement StatRequirements = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Attachments", Category="Beam")
	FOptionalArrayOfAnnouncementAttachment Attachments = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Client Data", Category="Beam")
	FOptionalMapOfString ClientData = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};