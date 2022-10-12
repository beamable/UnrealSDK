
#pragma once

#include "CoreMinimal.h"
#include "ImportFriendsRequestBody.h"

#include "ImportFriendsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UImportFriendsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ImportFriendsRequestBody To JSON String")
	static FString ImportFriendsRequestBodyToJsonString(const UImportFriendsRequestBody* Serializable, const bool Pretty);		
};