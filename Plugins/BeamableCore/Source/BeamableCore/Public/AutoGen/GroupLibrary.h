
#pragma once

#include "CoreMinimal.h"
#include "Group.h"

#include "GroupLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGroupLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Group To JSON String")
	static FString GroupToJsonString(const UGroup* Serializable, const bool Pretty);		
};