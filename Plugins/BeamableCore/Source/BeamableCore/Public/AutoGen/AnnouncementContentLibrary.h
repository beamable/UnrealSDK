#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AnnouncementContent.h"

#include "AnnouncementContentLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAnnouncementContentLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Json", DisplayName="AnnouncementContent To JSON String")
	static FString AnnouncementContentToJsonString(const UAnnouncementContent* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make AnnouncementContent", meta=(DefaultToSelf="Outer", AdvancedDisplay="StartDate, Gift, EndDate, Tags, StatRequirements, Attachments, ClientData, Outer", NativeMakeFunc))
	static UAnnouncementContent* Make(FString Body, FString Channel, FString Symbol, FString Title, FString Summary, FOptionalString StartDate, FOptionalPlayerReward Gift, FOptionalString EndDate, FOptionalArrayOfString Tags, FOptionalArrayOfPlayerStatRequirement StatRequirements, FOptionalArrayOfAnnouncementAttachment Attachments, FOptionalMapOfString ClientData, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Break AnnouncementContent", meta=(NativeBreakFunc))
	static void Break(const UAnnouncementContent* Serializable, FString& Body, FString& Channel, FString& Symbol, FString& Title, FString& Summary, FOptionalString& StartDate, FOptionalPlayerReward& Gift, FOptionalString& EndDate, FOptionalArrayOfString& Tags, FOptionalArrayOfPlayerStatRequirement& StatRequirements, FOptionalArrayOfAnnouncementAttachment& Attachments, FOptionalMapOfString& ClientData);
};