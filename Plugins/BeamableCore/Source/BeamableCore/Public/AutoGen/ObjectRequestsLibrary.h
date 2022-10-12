
#pragma once

#include "CoreMinimal.h"
#include "ObjectRequests.h"

#include "ObjectRequestsLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectRequestsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ObjectRequests To JSON String")
	static FString ObjectRequestsToJsonString(const UObjectRequests* Serializable, const bool Pretty);		
};