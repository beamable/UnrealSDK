
#pragma once

#include "CoreMinimal.h"
#include "MakeFriendshipRequestBody.h"

#include "MakeFriendshipRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMakeFriendshipRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize MakeFriendshipRequestBody To JSON String")
	static FString MakeFriendshipRequestBodyToJsonString(const UMakeFriendshipRequestBody* Serializable, const bool Pretty);		
};