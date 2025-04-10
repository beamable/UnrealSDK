#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AnnouncementView.h"

#include "AnnouncementViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAnnouncementViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Json", DisplayName="AnnouncementView To JSON String")
	static FString AnnouncementViewToJsonString(const UAnnouncementView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make AnnouncementView", meta=(DefaultToSelf="Outer", AdvancedDisplay="EndDate, Gift, SecondsRemaining, StartDate, Tags, Outer", NativeMakeFunc))
	static UAnnouncementView* Make(bool bIsClaimed, bool bIsDeleted, bool bIsRead, FString Body, FString Channel, FString Id, FString Title, FString Summary, TArray<UClientDataEntry*> ClientDataList, TArray<UAnnouncementAttachment*> Attachments, FOptionalString EndDate, FOptionalPlayerReward Gift, FOptionalInt64 SecondsRemaining, FOptionalString StartDate, FOptionalArrayOfString Tags, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Break AnnouncementView", meta=(NativeBreakFunc))
	static void Break(const UAnnouncementView* Serializable, bool& bIsClaimed, bool& bIsDeleted, bool& bIsRead, FString& Body, FString& Channel, FString& Id, FString& Title, FString& Summary, TArray<UClientDataEntry*>& ClientDataList, TArray<UAnnouncementAttachment*>& Attachments, FOptionalString& EndDate, FOptionalPlayerReward& Gift, FOptionalInt64& SecondsRemaining, FOptionalString& StartDate, FOptionalArrayOfString& Tags);
};