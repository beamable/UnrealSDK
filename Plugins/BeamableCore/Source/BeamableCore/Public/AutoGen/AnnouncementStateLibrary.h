#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AnnouncementState.h"

#include "AnnouncementStateLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAnnouncementStateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|4 - Json", DisplayName="AnnouncementState To JSON String")
	static FString AnnouncementStateToJsonString(const UAnnouncementState* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|3 - Backend", DisplayName="Make AnnouncementState", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAnnouncementState* Make(bool bIsClaimed, bool bIsDeleted, bool bIsRead, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|3 - Backend", DisplayName="Break AnnouncementState", meta=(NativeBreakFunc))
	static void Break(const UAnnouncementState* Serializable, bool& bIsClaimed, bool& bIsDeleted, bool& bIsRead);
};