#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SearchAnnouncementsRequestBody.h"

#include "SearchAnnouncementsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USearchAnnouncementsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Json", DisplayName="SearchAnnouncementsRequestBody To JSON String")
	static FString SearchAnnouncementsRequestBodyToJsonString(const USearchAnnouncementsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make SearchAnnouncementsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Date, Outer", NativeMakeFunc))
	static USearchAnnouncementsRequestBody* Make(FOptionalString Date, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Break SearchAnnouncementsRequestBody", meta=(NativeBreakFunc))
	static void Break(const USearchAnnouncementsRequestBody* Serializable, FOptionalString& Date);
};