
#pragma once

#include "CoreMinimal.h"
#include "RealmConfigSaveRequestBody.h"

#include "RealmConfigSaveRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URealmConfigSaveRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RealmConfigSaveRequestBody To JSON String")
	static FString RealmConfigSaveRequestBodyToJsonString(const URealmConfigSaveRequestBody* Serializable, const bool Pretty);		
};