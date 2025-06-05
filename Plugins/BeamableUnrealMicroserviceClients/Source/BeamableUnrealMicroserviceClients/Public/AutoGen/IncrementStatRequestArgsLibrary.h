#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/IncrementStatRequestArgs.h"

#include "IncrementStatRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UIncrementStatRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|LiveOpsDemoMS|Utils|Json", DisplayName="IncrementStatRequestArgs To JSON String")
	static FString IncrementStatRequestArgsToJsonString(const UIncrementStatRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|LiveOpsDemoMS|Utils|Make/Break", DisplayName="Make IncrementStatRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UIncrementStatRequestArgs* Make(int64 GamerTag, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|LiveOpsDemoMS|Utils|Make/Break", DisplayName="Break IncrementStatRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UIncrementStatRequestArgs* Serializable, int64& GamerTag);
};