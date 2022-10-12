
#pragma once

#include "CoreMinimal.h"
#include "AnnouncementContent.h"

#include "AnnouncementContentLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAnnouncementContentLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AnnouncementContent To JSON String")
	static FString AnnouncementContentToJsonString(const UAnnouncementContent* Serializable, const bool Pretty);		
};