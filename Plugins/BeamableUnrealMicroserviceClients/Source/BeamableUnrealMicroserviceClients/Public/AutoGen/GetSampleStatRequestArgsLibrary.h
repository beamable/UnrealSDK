#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetSampleStatRequestArgs.h"

#include "GetSampleStatRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UGetSampleStatRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|LiveOpsDemoMS|Utils|Json", DisplayName="GetSampleStatRequestArgs To JSON String")
	static FString GetSampleStatRequestArgsToJsonString(const UGetSampleStatRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|LiveOpsDemoMS|Utils|Make/Break", DisplayName="Make GetSampleStatRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetSampleStatRequestArgs* Make(int64 GamerTag, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|LiveOpsDemoMS|Utils|Make/Break", DisplayName="Break GetSampleStatRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UGetSampleStatRequestArgs* Serializable, int64& GamerTag);
};