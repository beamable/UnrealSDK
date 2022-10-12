
#pragma once

#include "CoreMinimal.h"
#include "GroupUser.h"

#include "GroupUserLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGroupUserLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GroupUser To JSON String")
	static FString GroupUserToJsonString(const UGroupUser* Serializable, const bool Pretty);		
};