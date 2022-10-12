
#pragma once

#include "CoreMinimal.h"
#include "ListMailCategoriesResponse.h"

#include "ListMailCategoriesResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UListMailCategoriesResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ListMailCategoriesResponse To JSON String")
	static FString ListMailCategoriesResponseToJsonString(const UListMailCategoriesResponse* Serializable, const bool Pretty);		
};