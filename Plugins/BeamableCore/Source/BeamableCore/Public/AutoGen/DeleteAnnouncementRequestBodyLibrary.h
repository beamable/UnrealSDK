#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/DeleteAnnouncementRequestBody.h"

#include "DeleteAnnouncementRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDeleteAnnouncementRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Json", DisplayName="DeleteAnnouncementRequestBody To JSON String")
	static FString DeleteAnnouncementRequestBodyToJsonString(const UDeleteAnnouncementRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make DeleteAnnouncementRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UDeleteAnnouncementRequestBody* Make(FString Symbol, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Break DeleteAnnouncementRequestBody", meta=(NativeBreakFunc))
	static void Break(const UDeleteAnnouncementRequestBody* Serializable, FString& Symbol);
};