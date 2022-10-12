
#pragma once

#include "CoreMinimal.h"
#include "SendFriendRequestBody.h"

#include "SendFriendRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USendFriendRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SendFriendRequestBody To JSON String")
	static FString SendFriendRequestBodyToJsonString(const USendFriendRequestBody* Serializable, const bool Pretty);		
};