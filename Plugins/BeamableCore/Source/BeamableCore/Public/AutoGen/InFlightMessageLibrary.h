#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/InFlightMessage.h"

#include "InFlightMessageLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UInFlightMessageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Admin|Utils|Json", DisplayName="InFlightMessage To JSON String")
	static FString InFlightMessageToJsonString(const UInFlightMessage* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Admin|Utils|Make/Break", DisplayName="Make InFlightMessage", meta=(DefaultToSelf="Outer", AdvancedDisplay="bLimitFailureRetries, Shard, GamerTag, Outer", NativeMakeFunc))
	static UInFlightMessage* Make(FString Service, FString Id, FString Method, FString Path, FString Body, FOptionalBool bLimitFailureRetries, FOptionalString Shard, FOptionalInt64 GamerTag, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Admin|Utils|Make/Break", DisplayName="Break InFlightMessage", meta=(NativeBreakFunc))
	static void Break(const UInFlightMessage* Serializable, FString& Service, FString& Id, FString& Method, FString& Path, FString& Body, FOptionalBool& bLimitFailureRetries, FOptionalString& Shard, FOptionalInt64& GamerTag);
};