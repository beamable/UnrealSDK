
#pragma once

#include "CoreMinimal.h"
#include "GetChampionsResponse.h"

#include "GetChampionsResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetChampionsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetChampionsResponse To JSON String")
	static FString GetChampionsResponseToJsonString(const UGetChampionsResponse* Serializable, const bool Pretty);		
};