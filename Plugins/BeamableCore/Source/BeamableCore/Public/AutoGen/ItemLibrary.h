
#pragma once

#include "CoreMinimal.h"
#include "Item.h"

#include "ItemLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UItemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Item To JSON String")
	static FString ItemToJsonString(const UItem* Serializable, const bool Pretty);		
};