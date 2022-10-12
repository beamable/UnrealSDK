
#pragma once

#include "CoreMinimal.h"
#include "GroupCreate.h"

#include "GroupCreateLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGroupCreateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GroupCreate To JSON String")
	static FString GroupCreateToJsonString(const UGroupCreate* Serializable, const bool Pretty);		
};