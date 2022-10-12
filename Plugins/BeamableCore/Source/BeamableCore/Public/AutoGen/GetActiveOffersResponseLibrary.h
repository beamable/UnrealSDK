
#pragma once

#include "CoreMinimal.h"
#include "GetActiveOffersResponse.h"

#include "GetActiveOffersResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetActiveOffersResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetActiveOffersResponse To JSON String")
	static FString GetActiveOffersResponseToJsonString(const UGetActiveOffersResponse* Serializable, const bool Pretty);		
};