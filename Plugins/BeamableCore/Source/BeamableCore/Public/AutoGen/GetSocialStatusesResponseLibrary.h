
#pragma once

#include "CoreMinimal.h"
#include "GetSocialStatusesResponse.h"

#include "GetSocialStatusesResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetSocialStatusesResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetSocialStatusesResponse To JSON String")
	static FString GetSocialStatusesResponseToJsonString(const UGetSocialStatusesResponse* Serializable, const bool Pretty);		
};