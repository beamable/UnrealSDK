
#pragma once

#include "CoreMinimal.h"
#include "ItemGroup.h"

#include "ItemGroupLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UItemGroupLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ItemGroup To JSON String")
	static FString ItemGroupToJsonString(const UItemGroup* Serializable, const bool Pretty);		
};