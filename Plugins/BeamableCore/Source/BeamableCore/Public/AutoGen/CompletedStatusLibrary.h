
#pragma once

#include "CoreMinimal.h"
#include "CompletedStatus.h"

#include "CompletedStatusLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCompletedStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CompletedStatus To JSON String")
	static FString CompletedStatusToJsonString(const UCompletedStatus* Serializable, const bool Pretty);		
};