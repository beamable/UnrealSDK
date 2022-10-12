
#pragma once

#include "CoreMinimal.h"
#include "DeleteAnnouncementRequestBody.h"

#include "DeleteAnnouncementRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteAnnouncementRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize DeleteAnnouncementRequestBody To JSON String")
	static FString DeleteAnnouncementRequestBodyToJsonString(const UDeleteAnnouncementRequestBody* Serializable, const bool Pretty);		
};