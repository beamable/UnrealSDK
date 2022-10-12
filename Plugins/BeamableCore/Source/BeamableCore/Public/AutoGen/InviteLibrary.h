
#pragma once

#include "CoreMinimal.h"
#include "Invite.h"

#include "InviteLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UInviteLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Invite To JSON String")
	static FString InviteToJsonString(const UInvite* Serializable, const bool Pretty);		
};