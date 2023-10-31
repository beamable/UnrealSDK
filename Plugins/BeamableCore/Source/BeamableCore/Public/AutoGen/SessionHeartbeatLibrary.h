#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SessionHeartbeat.h"

#include "SessionHeartbeatLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USessionHeartbeatLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - SessionHeartbeat To JSON String")
	static FString SessionHeartbeatToJsonString(const USessionHeartbeat* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make SessionHeartbeat", meta=(DefaultToSelf="Outer", AdvancedDisplay="Heartbeat, Outer", NativeMakeFunc))
	static USessionHeartbeat* Make(int64 Gt, FOptionalInt64 Heartbeat, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break SessionHeartbeat", meta=(NativeBreakFunc))
	static void Break(const USessionHeartbeat* Serializable, int64& Gt, FOptionalInt64& Heartbeat);
};