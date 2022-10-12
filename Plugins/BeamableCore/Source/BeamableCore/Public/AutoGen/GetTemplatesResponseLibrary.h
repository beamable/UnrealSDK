
#pragma once

#include "CoreMinimal.h"
#include "GetTemplatesResponse.h"

#include "GetTemplatesResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetTemplatesResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetTemplatesResponse To JSON String")
	static FString GetTemplatesResponseToJsonString(const UGetTemplatesResponse* Serializable, const bool Pretty);		
};