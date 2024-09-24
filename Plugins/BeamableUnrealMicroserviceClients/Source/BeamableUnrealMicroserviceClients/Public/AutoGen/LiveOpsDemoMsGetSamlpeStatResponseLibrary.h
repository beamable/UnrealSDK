#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMsGetSamlpeStatResponse.h"

#include "LiveOpsDemoMsGetSamlpeStatResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API ULiveOpsDemoMsGetSamlpeStatResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LiveOpsDemoMsGetSamlpeStatResponse To JSON String")
	static FString LiveOpsDemoMsGetSamlpeStatResponseToJsonString(const ULiveOpsDemoMsGetSamlpeStatResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LiveOpsDemoMsGetSamlpeStatResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULiveOpsDemoMsGetSamlpeStatResponse* Make(int32 Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LiveOpsDemoMsGetSamlpeStatResponse", meta=(NativeBreakFunc))
	static void Break(const ULiveOpsDemoMsGetSamlpeStatResponse* Serializable, int32& Value);
};