
#pragma once

#include "CoreMinimal.h"
#include "GroupMembershipRequestBody.h"

#include "GroupMembershipRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGroupMembershipRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GroupMembershipRequestBody To JSON String")
	static FString GroupMembershipRequestBodyToJsonString(const UGroupMembershipRequestBody* Serializable, const bool Pretty);		
};