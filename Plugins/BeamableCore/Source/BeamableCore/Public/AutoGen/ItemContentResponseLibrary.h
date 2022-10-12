
#pragma once

#include "CoreMinimal.h"
#include "ItemContentResponse.h"

#include "ItemContentResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UItemContentResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ItemContentResponse To JSON String")
	static FString ItemContentResponseToJsonString(const UItemContentResponse* Serializable, const bool Pretty);		
};