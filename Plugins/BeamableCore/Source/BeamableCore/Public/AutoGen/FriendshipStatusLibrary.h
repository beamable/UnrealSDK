
#pragma once

#include "CoreMinimal.h"
#include "FriendshipStatus.h"

#include "FriendshipStatusLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UFriendshipStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize FriendshipStatus To JSON String")
	static FString FriendshipStatusToJsonString(const UFriendshipStatus* Serializable, const bool Pretty);		
};