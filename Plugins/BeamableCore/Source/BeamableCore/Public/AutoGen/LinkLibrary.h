
#pragma once

#include "CoreMinimal.h"
#include "Link.h"

#include "LinkLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULinkLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Link To JSON String")
	static FString LinkToJsonString(const ULink* Serializable, const bool Pretty);		
};