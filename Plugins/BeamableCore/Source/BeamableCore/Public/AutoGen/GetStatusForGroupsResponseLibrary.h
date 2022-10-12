
#pragma once

#include "CoreMinimal.h"
#include "GetStatusForGroupsResponse.h"

#include "GetStatusForGroupsResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetStatusForGroupsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetStatusForGroupsResponse To JSON String")
	static FString GetStatusForGroupsResponseToJsonString(const UGetStatusForGroupsResponse* Serializable, const bool Pretty);		
};