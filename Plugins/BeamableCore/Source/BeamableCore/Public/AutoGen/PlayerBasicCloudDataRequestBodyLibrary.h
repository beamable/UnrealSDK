#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PlayerBasicCloudDataRequestBody.h"

#include "PlayerBasicCloudDataRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPlayerBasicCloudDataRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|Utils|Json", DisplayName="PlayerBasicCloudDataRequestBody To JSON String")
	static FString PlayerBasicCloudDataRequestBodyToJsonString(const UPlayerBasicCloudDataRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|Utils|Make/Break", DisplayName="Make PlayerBasicCloudDataRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="PlayerId, Outer", NativeMakeFunc))
	static UPlayerBasicCloudDataRequestBody* Make(FOptionalInt64 PlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|Utils|Make/Break", DisplayName="Break PlayerBasicCloudDataRequestBody", meta=(NativeBreakFunc))
	static void Break(const UPlayerBasicCloudDataRequestBody* Serializable, FOptionalInt64& PlayerId);
};