
#pragma once

#include "CoreMinimal.h"
#include "PromoteRealmResponse.h"

#include "PromoteRealmResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPromoteRealmResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PromoteRealmResponse To JSON String")
	static FString PromoteRealmResponseToJsonString(const UPromoteRealmResponse* Serializable, const bool Pretty);		
};