
#pragma once

#include "CoreMinimal.h"
#include "GroupMembershipResponse.h"

#include "GroupMembershipResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGroupMembershipResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GroupMembershipResponse To JSON String")
	static FString GroupMembershipResponseToJsonString(const UGroupMembershipResponse* Serializable, const bool Pretty);		
};