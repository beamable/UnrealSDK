
#pragma once

#include "CoreMinimal.h"
#include "ContextInfo.h"

#include "ContextInfoLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UContextInfoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ContextInfo To JSON String")
	static FString ContextInfoToJsonString(const UContextInfo* Serializable, const bool Pretty);		
};