
#pragma once

#include "CoreMinimal.h"
#include "GroupStatus.h"

#include "GroupStatusLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGroupStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GroupStatus To JSON String")
	static FString GroupStatusToJsonString(const UGroupStatus* Serializable, const bool Pretty);		
};