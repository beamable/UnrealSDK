#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/InFlightMessage.h"

#include "InFlightMessageLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UInFlightMessageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - InFlightMessage To JSON String")
	static FString InFlightMessageToJsonString(const UInFlightMessage* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make InFlightMessage", meta=(DefaultToSelf="Outer", AdvancedDisplay="bLimitFailureRetries, GamerTag, Shard, Outer", NativeMakeFunc))
	static UInFlightMessage* Make(FString Method, FString Body, FString Path, FString Service, FString Id, FOptionalBool bLimitFailureRetries, FOptionalInt64 GamerTag, FOptionalString Shard, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break InFlightMessage", meta=(NativeBreakFunc))
	static void Break(const UInFlightMessage* Serializable, FString& Method, FString& Body, FString& Path, FString& Service, FString& Id, FOptionalBool& bLimitFailureRetries, FOptionalInt64& GamerTag, FOptionalString& Shard);
};