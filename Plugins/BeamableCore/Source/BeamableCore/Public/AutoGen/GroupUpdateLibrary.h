
#pragma once

#include "CoreMinimal.h"
#include "GroupUpdate.h"

#include "GroupUpdateLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGroupUpdateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GroupUpdate To JSON String")
	static FString GroupUpdateToJsonString(const UGroupUpdate* Serializable, const bool Pretty);		
};