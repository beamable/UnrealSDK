
#pragma once

#include "CoreMinimal.h"
#include "GroupInvite.h"

#include "GroupInviteLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGroupInviteLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GroupInvite To JSON String")
	static FString GroupInviteToJsonString(const UGroupInvite* Serializable, const bool Pretty);		
};