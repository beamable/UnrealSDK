#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AnnouncementRawResponse.h"

#include "AnnouncementRawResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAnnouncementRawResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - AnnouncementRawResponse To JSON String")
	static FString AnnouncementRawResponseToJsonString(const UAnnouncementRawResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make AnnouncementRawResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAnnouncementRawResponse* Make(TMap<FString, UAnnouncementState*> Announcements, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break AnnouncementRawResponse", meta=(NativeBreakFunc))
	static void Break(const UAnnouncementRawResponse* Serializable, TMap<FString, UAnnouncementState*>& Announcements);
};