
#pragma once

#include "CoreMinimal.h"
#include "Friend.h"

#include "FriendLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UFriendLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Friend To JSON String")
	static FString FriendToJsonString(const UFriend* Serializable, const bool Pretty);		
};