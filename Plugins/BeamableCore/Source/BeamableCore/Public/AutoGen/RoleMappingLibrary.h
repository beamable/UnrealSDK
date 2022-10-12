
#pragma once

#include "CoreMinimal.h"
#include "RoleMapping.h"

#include "RoleMappingLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URoleMappingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RoleMapping To JSON String")
	static FString RoleMappingToJsonString(const URoleMapping* Serializable, const bool Pretty);		
};