#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventsBasicInFlightMessage.h"

#include "EventsBasicInFlightMessageLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventsBasicInFlightMessageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Json", DisplayName="EventsBasicInFlightMessage To JSON String")
	static FString EventsBasicInFlightMessageToJsonString(const UEventsBasicInFlightMessage* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Make EventsBasicInFlightMessage", meta=(DefaultToSelf="Outer", AdvancedDisplay="bLimitFailureRetries, GamerTag, Shard, Outer", NativeMakeFunc))
	static UEventsBasicInFlightMessage* Make(FString Method, FString Body, FString Path, FString Service, FString Id, FOptionalBool bLimitFailureRetries, FOptionalInt64 GamerTag, FOptionalString Shard, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Break EventsBasicInFlightMessage", meta=(NativeBreakFunc))
	static void Break(const UEventsBasicInFlightMessage* Serializable, FString& Method, FString& Body, FString& Path, FString& Service, FString& Id, FOptionalBool& bLimitFailureRetries, FOptionalInt64& GamerTag, FOptionalString& Shard);
};