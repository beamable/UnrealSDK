#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AnnouncementQuery.h"

#include "AnnouncementQueryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAnnouncementQueryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Json", DisplayName="AnnouncementQuery To JSON String")
	static FString AnnouncementQueryToJsonString(const UAnnouncementQuery* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make AnnouncementQuery", meta=(DefaultToSelf="Outer", AdvancedDisplay="bIncludeDeleted, Outer", NativeMakeFunc))
	static UAnnouncementQuery* Make(FOptionalBool bIncludeDeleted, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Break AnnouncementQuery", meta=(NativeBreakFunc))
	static void Break(const UAnnouncementQuery* Serializable, FOptionalBool& bIncludeDeleted);
};