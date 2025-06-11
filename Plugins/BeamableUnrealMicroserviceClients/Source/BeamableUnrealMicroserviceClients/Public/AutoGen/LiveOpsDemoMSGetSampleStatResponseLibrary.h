#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSGetSampleStatResponse.h"

#include "LiveOpsDemoMSGetSampleStatResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API ULiveOpsDemoMSGetSampleStatResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|LiveOpsDemoMS|Utils|Json", DisplayName="LiveOpsDemoMSGetSampleStatResponse To JSON String")
	static FString LiveOpsDemoMSGetSampleStatResponseToJsonString(const ULiveOpsDemoMSGetSampleStatResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|LiveOpsDemoMS|Utils|Make/Break", DisplayName="Make LiveOpsDemoMSGetSampleStatResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULiveOpsDemoMSGetSampleStatResponse* Make(int32 Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|LiveOpsDemoMS|Utils|Make/Break", DisplayName="Break LiveOpsDemoMSGetSampleStatResponse", meta=(NativeBreakFunc))
	static void Break(const ULiveOpsDemoMSGetSampleStatResponse* Serializable, int32& Value);
};