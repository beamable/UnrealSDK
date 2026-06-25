#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendPushToSelfRequestArgs.h"

#include "SendPushToSelfRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API USendPushToSelfRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="SendPushToSelfRequestArgs To JSON String")
	static FString SendPushToSelfRequestArgsToJsonString(const USendPushToSelfRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make SendPushToSelfRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USendPushToSelfRequestArgs* Make(FString Title, FString Body, FString DeepLink, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break SendPushToSelfRequestArgs", meta=(NativeBreakFunc))
	static void Break(const USendPushToSelfRequestArgs* Serializable, FString& Title, FString& Body, FString& DeepLink);
};