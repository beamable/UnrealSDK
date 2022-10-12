
#pragma once

#include "CoreMinimal.h"
#include "ClientPermission.h"

#include "ClientPermissionLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UClientPermissionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ClientPermission To JSON String")
	static FString ClientPermissionToJsonString(const UClientPermission* Serializable, const bool Pretty);		
};