
#pragma once

#include "CoreMinimal.h"
#include "ListTokenResponseItem.h"

#include "ListTokenResponseItemLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UListTokenResponseItemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ListTokenResponseItem To JSON String")
	static FString ListTokenResponseItemToJsonString(const UListTokenResponseItem* Serializable, const bool Pretty);		
};