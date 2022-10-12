
#pragma once

#include "CoreMinimal.h"
#include "GroupRole.h"

#include "GroupRoleLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGroupRoleLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GroupRole To JSON String")
	static FString GroupRoleToJsonString(const UGroupRole* Serializable, const bool Pretty);		
};