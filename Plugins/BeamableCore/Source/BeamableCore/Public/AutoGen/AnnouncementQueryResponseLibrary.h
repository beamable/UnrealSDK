#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AnnouncementQueryResponse.h"

#include "AnnouncementQueryResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAnnouncementQueryResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - AnnouncementQueryResponse To JSON String")
	static FString AnnouncementQueryResponseToJsonString(const UAnnouncementQueryResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make AnnouncementQueryResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAnnouncementQueryResponse* Make(TArray<UAnnouncementView*> Announcements, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break AnnouncementQueryResponse", meta=(NativeBreakFunc))
	static void Break(const UAnnouncementQueryResponse* Serializable, TArray<UAnnouncementView*>& Announcements);
};