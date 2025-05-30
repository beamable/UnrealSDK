#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SuiFederationGetSuiEnvironmentResponse.h"

#include "SuiFederationGetSuiEnvironmentResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API USuiFederationGetSuiEnvironmentResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - SuiFederationGetSuiEnvironmentResponse To JSON String")
	static FString SuiFederationGetSuiEnvironmentResponseToJsonString(const USuiFederationGetSuiEnvironmentResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make SuiFederationGetSuiEnvironmentResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USuiFederationGetSuiEnvironmentResponse* Make(FString Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break SuiFederationGetSuiEnvironmentResponse", meta=(NativeBreakFunc))
	static void Break(const USuiFederationGetSuiEnvironmentResponse* Serializable, FString& Value);
};