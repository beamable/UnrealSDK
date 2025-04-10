#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AnnouncementRequestBody.h"

#include "AnnouncementRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAnnouncementRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Json", DisplayName="AnnouncementRequestBody To JSON String")
	static FString AnnouncementRequestBodyToJsonString(const UAnnouncementRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make AnnouncementRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Announcement, Announcements, Outer", NativeMakeFunc))
	static UAnnouncementRequestBody* Make(FOptionalString Announcement, FOptionalArrayOfString Announcements, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Break AnnouncementRequestBody", meta=(NativeBreakFunc))
	static void Break(const UAnnouncementRequestBody* Serializable, FOptionalString& Announcement, FOptionalArrayOfString& Announcements);
};