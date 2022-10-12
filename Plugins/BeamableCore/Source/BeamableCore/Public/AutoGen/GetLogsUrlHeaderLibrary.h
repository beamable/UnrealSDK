
#pragma once

#include "CoreMinimal.h"
#include "GetLogsUrlHeader.h"

#include "GetLogsUrlHeaderLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetLogsUrlHeaderLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetLogsUrlHeader To JSON String")
	static FString GetLogsUrlHeaderToJsonString(const UGetLogsUrlHeader* Serializable, const bool Pretty);		
};