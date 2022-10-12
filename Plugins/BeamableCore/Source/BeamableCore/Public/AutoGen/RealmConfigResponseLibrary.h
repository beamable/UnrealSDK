
#pragma once

#include "CoreMinimal.h"
#include "RealmConfigResponse.h"

#include "RealmConfigResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URealmConfigResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RealmConfigResponse To JSON String")
	static FString RealmConfigResponseToJsonString(const URealmConfigResponse* Serializable, const bool Pretty);		
};