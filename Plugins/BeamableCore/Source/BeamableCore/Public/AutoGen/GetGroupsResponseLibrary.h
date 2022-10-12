
#pragma once

#include "CoreMinimal.h"
#include "GetGroupsResponse.h"

#include "GetGroupsResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetGroupsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetGroupsResponse To JSON String")
	static FString GetGroupsResponseToJsonString(const UGetGroupsResponse* Serializable, const bool Pretty);		
};