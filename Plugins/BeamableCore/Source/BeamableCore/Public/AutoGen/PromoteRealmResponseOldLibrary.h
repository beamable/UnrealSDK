
#pragma once

#include "CoreMinimal.h"
#include "PromoteRealmResponseOld.h"

#include "PromoteRealmResponseOldLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPromoteRealmResponseOldLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PromoteRealmResponseOld To JSON String")
	static FString PromoteRealmResponseOldToJsonString(const UPromoteRealmResponseOld* Serializable, const bool Pretty);		
};