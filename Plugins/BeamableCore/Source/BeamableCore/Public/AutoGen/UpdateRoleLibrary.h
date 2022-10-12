
#pragma once

#include "CoreMinimal.h"
#include "UpdateRole.h"

#include "UpdateRoleLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UUpdateRoleLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize UpdateRole To JSON String")
	static FString UpdateRoleToJsonString(const UUpdateRole* Serializable, const bool Pretty);		
};