
#pragma once

#include "CoreMinimal.h"
#include "GetPlayerStatusResponse.h"

#include "GetPlayerStatusResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetPlayerStatusResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetPlayerStatusResponse To JSON String")
	static FString GetPlayerStatusResponseToJsonString(const UGetPlayerStatusResponse* Serializable, const bool Pretty);		
};