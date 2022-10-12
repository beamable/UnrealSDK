
#pragma once

#include "CoreMinimal.h"
#include "MultipliersGetResponse.h"

#include "MultipliersGetResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMultipliersGetResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize MultipliersGetResponse To JSON String")
	static FString MultipliersGetResponseToJsonString(const UMultipliersGetResponse* Serializable, const bool Pretty);		
};