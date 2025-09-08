#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventsObjectInFlightMessage.h"

#include "EventsObjectInFlightMessageLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventsObjectInFlightMessageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Json", DisplayName="EventsObjectInFlightMessage To JSON String")
	static FString EventsObjectInFlightMessageToJsonString(const UEventsObjectInFlightMessage* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Make EventsObjectInFlightMessage", meta=(DefaultToSelf="Outer", AdvancedDisplay="bLimitFailureRetries, GamerTag, Shard, Outer", NativeMakeFunc))
	static UEventsObjectInFlightMessage* Make(FString Method, FString Body, FString Path, FString Service, FString Id, FOptionalBool bLimitFailureRetries, FOptionalInt64 GamerTag, FOptionalString Shard, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Break EventsObjectInFlightMessage", meta=(NativeBreakFunc))
	static void Break(const UEventsObjectInFlightMessage* Serializable, FString& Method, FString& Body, FString& Path, FString& Service, FString& Id, FOptionalBool& bLimitFailureRetries, FOptionalInt64& GamerTag, FOptionalString& Shard);
};