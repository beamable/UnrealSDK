#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AnnouncementContentResponse.h"

#include "AnnouncementContentResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAnnouncementContentResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - AnnouncementContentResponse To JSON String")
	static FString AnnouncementContentResponseToJsonString(const UAnnouncementContentResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make AnnouncementContentResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAnnouncementContentResponse* Make(TArray<UAnnouncementContent*> Content, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break AnnouncementContentResponse", meta=(NativeBreakFunc))
	static void Break(const UAnnouncementContentResponse* Serializable, TArray<UAnnouncementContent*>& Content);
};