
#pragma once

#include "CoreMinimal.h"
#include "SearchAnnouncementsRequestBody.h"

#include "SearchAnnouncementsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USearchAnnouncementsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SearchAnnouncementsRequestBody To JSON String")
	static FString SearchAnnouncementsRequestBodyToJsonString(const USearchAnnouncementsRequestBody* Serializable, const bool Pretty);		
};