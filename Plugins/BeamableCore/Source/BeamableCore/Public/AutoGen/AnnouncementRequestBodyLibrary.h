
#pragma once

#include "CoreMinimal.h"
#include "AnnouncementRequestBody.h"

#include "AnnouncementRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAnnouncementRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AnnouncementRequestBody To JSON String")
	static FString AnnouncementRequestBodyToJsonString(const UAnnouncementRequestBody* Serializable, const bool Pretty);		
};