
#pragma once

#include "CoreMinimal.h"
#include "URLResponse.h"

#include "URLResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UURLResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize URLResponse To JSON String")
	static FString URLResponseToJsonString(const UURLResponse* Serializable, const bool Pretty);		
};