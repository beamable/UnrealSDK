
#pragma once

#include "CoreMinimal.h"
#include "AnnouncementView.h"

#include "AnnouncementViewLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAnnouncementViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AnnouncementView To JSON String")
	static FString AnnouncementViewToJsonString(const UAnnouncementView* Serializable, const bool Pretty);		
};