
#pragma once

#include "CoreMinimal.h"
#include "RealmsBasicAccount.h"

#include "RealmsBasicAccountLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URealmsBasicAccountLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RealmsBasicAccount To JSON String")
	static FString RealmsBasicAccountToJsonString(const URealmsBasicAccount* Serializable, const bool Pretty);		
};