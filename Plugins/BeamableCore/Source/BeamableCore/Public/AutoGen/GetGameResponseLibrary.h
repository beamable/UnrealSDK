
#pragma once

#include "CoreMinimal.h"
#include "GetGameResponse.h"

#include "GetGameResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetGameResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetGameResponse To JSON String")
	static FString GetGameResponseToJsonString(const UGetGameResponse* Serializable, const bool Pretty);		
};