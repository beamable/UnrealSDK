#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSGetSamlpeStatResponse.h"

#include "LiveOpsDemoMSGetSamlpeStatResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API ULiveOpsDemoMSGetSamlpeStatResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LiveOpsDemoMSGetSamlpeStatResponse To JSON String")
	static FString LiveOpsDemoMSGetSamlpeStatResponseToJsonString(const ULiveOpsDemoMSGetSamlpeStatResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LiveOpsDemoMSGetSamlpeStatResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULiveOpsDemoMSGetSamlpeStatResponse* Make(int32 Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LiveOpsDemoMSGetSamlpeStatResponse", meta=(NativeBreakFunc))
	static void Break(const ULiveOpsDemoMSGetSamlpeStatResponse* Serializable, int32& Value);
};