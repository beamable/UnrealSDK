
#pragma once

#include "CoreMinimal.h"
#include "AvailableRolesResponse.h"

#include "AvailableRolesResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAvailableRolesResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AvailableRolesResponse To JSON String")
	static FString AvailableRolesResponseToJsonString(const UAvailableRolesResponse* Serializable, const bool Pretty);		
};