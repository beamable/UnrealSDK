
#pragma once

#include "CoreMinimal.h"
#include "GetStatusResponse.h"

#include "GetStatusResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetStatusResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetStatusResponse To JSON String")
	static FString GetStatusResponseToJsonString(const UGetStatusResponse* Serializable, const bool Pretty);		
};