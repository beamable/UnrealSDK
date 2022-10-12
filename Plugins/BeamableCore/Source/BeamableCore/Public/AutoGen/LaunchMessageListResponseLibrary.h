
#pragma once

#include "CoreMinimal.h"
#include "LaunchMessageListResponse.h"

#include "LaunchMessageListResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULaunchMessageListResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LaunchMessageListResponse To JSON String")
	static FString LaunchMessageListResponseToJsonString(const ULaunchMessageListResponse* Serializable, const bool Pretty);		
};