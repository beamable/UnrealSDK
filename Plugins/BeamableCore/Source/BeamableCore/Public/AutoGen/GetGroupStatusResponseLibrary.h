
#pragma once

#include "CoreMinimal.h"
#include "GetGroupStatusResponse.h"

#include "GetGroupStatusResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetGroupStatusResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetGroupStatusResponse To JSON String")
	static FString GetGroupStatusResponseToJsonString(const UGetGroupStatusResponse* Serializable, const bool Pretty);		
};