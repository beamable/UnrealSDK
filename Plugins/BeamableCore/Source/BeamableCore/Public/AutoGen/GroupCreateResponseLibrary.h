
#pragma once

#include "CoreMinimal.h"
#include "GroupCreateResponse.h"

#include "GroupCreateResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGroupCreateResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GroupCreateResponse To JSON String")
	static FString GroupCreateResponseToJsonString(const UGroupCreateResponse* Serializable, const bool Pretty);		
};