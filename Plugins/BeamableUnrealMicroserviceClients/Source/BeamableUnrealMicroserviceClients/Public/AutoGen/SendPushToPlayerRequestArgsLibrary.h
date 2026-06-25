#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendPushToPlayerRequestArgs.h"

#include "SendPushToPlayerRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API USendPushToPlayerRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="SendPushToPlayerRequestArgs To JSON String")
	static FString SendPushToPlayerRequestArgsToJsonString(const USendPushToPlayerRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make SendPushToPlayerRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USendPushToPlayerRequestArgs* Make(int64 PlayerId, FString Title, FString Body, FString DeepLink, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break SendPushToPlayerRequestArgs", meta=(NativeBreakFunc))
	static void Break(const USendPushToPlayerRequestArgs* Serializable, int64& PlayerId, FString& Title, FString& Body, FString& DeepLink);
};