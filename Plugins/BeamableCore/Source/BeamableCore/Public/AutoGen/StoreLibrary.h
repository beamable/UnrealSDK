
#pragma once

#include "CoreMinimal.h"
#include "Store.h"

#include "StoreLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UStoreLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Store To JSON String")
	static FString StoreToJsonString(const UStore* Serializable, const bool Pretty);		
};