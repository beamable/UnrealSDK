#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/IncrementStatRequestArgs.h"

#include "IncrementStatRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UIncrementStatRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - IncrementStatRequestArgs To JSON String")
	static FString IncrementStatRequestArgsToJsonString(const UIncrementStatRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make IncrementStatRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UIncrementStatRequestArgs* Make(int64 UserID, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break IncrementStatRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UIncrementStatRequestArgs* Serializable, int64& UserID);
};