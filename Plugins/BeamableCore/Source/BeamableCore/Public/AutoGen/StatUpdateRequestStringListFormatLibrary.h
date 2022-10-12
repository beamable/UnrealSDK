
#pragma once

#include "CoreMinimal.h"
#include "StatUpdateRequestStringListFormat.h"

#include "StatUpdateRequestStringListFormatLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UStatUpdateRequestStringListFormatLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize StatUpdateRequestStringListFormat To JSON String")
	static FString StatUpdateRequestStringListFormatToJsonString(const UStatUpdateRequestStringListFormat* Serializable, const bool Pretty);		
};