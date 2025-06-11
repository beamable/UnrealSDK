#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AnnouncementDto.h"

#include "AnnouncementDtoLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAnnouncementDtoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Json", DisplayName="AnnouncementDto To JSON String")
	static FString AnnouncementDtoToJsonString(const UAnnouncementDto* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make AnnouncementDto", meta=(DefaultToSelf="Outer", AdvancedDisplay="StartDate, Gift, EndDate, Tags, StatRequirements, Attachments, ClientData, Outer", NativeMakeFunc))
	static UAnnouncementDto* Make(ULocalizationRef* Body, FString Channel, FString Symbol, ULocalizationRef* Title, ULocalizationRef* Summary, FOptionalString StartDate, FOptionalPlayerReward Gift, FOptionalString EndDate, FOptionalArrayOfString Tags, FOptionalArrayOfPlayerStatRequirement StatRequirements, FOptionalArrayOfAnnouncementAttachment Attachments, FOptionalMapOfString ClientData, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Break AnnouncementDto", meta=(NativeBreakFunc))
	static void Break(const UAnnouncementDto* Serializable, ULocalizationRef*& Body, FString& Channel, FString& Symbol, ULocalizationRef*& Title, ULocalizationRef*& Summary, FOptionalString& StartDate, FOptionalPlayerReward& Gift, FOptionalString& EndDate, FOptionalArrayOfString& Tags, FOptionalArrayOfPlayerStatRequirement& StatRequirements, FOptionalArrayOfAnnouncementAttachment& Attachments, FOptionalMapOfString& ClientData);
};