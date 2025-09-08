#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AdminActorInFlightMessage.h"

#include "AdminActorInFlightMessageLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAdminActorInFlightMessageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Admin|Utils|Json", DisplayName="AdminActorInFlightMessage To JSON String")
	static FString AdminActorInFlightMessageToJsonString(const UAdminActorInFlightMessage* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Admin|Utils|Make/Break", DisplayName="Make AdminActorInFlightMessage", meta=(DefaultToSelf="Outer", AdvancedDisplay="bLimitFailureRetries, Shard, GamerTag, Outer", NativeMakeFunc))
	static UAdminActorInFlightMessage* Make(FString Service, FString MessageId, FString Method, FString Path, FString Body, FOptionalBool bLimitFailureRetries, FOptionalString Shard, FOptionalInt64 GamerTag, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Admin|Utils|Make/Break", DisplayName="Break AdminActorInFlightMessage", meta=(NativeBreakFunc))
	static void Break(const UAdminActorInFlightMessage* Serializable, FString& Service, FString& MessageId, FString& Method, FString& Path, FString& Body, FOptionalBool& bLimitFailureRetries, FOptionalString& Shard, FOptionalInt64& GamerTag);
};