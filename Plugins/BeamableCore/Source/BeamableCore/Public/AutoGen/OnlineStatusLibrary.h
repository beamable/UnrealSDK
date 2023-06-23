#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/OnlineStatus.h"

#include "OnlineStatusLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UOnlineStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - OnlineStatus To JSON String")
	static FString OnlineStatusToJsonString(const UOnlineStatus* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make OnlineStatus", meta=(DefaultToSelf="Outer", AdvancedDisplay="LastOnline, bOnline, PlayerId, Status, Description, Outer", NativeMakeFunc))
	static UOnlineStatus* Make(FOptionalString LastOnline, FOptionalBool bOnline, FOptionalString PlayerId, FOptionalPresenceStatus Status, FOptionalString Description, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break OnlineStatus", meta=(NativeBreakFunc))
	static void Break(const UOnlineStatus* Serializable, FOptionalString& LastOnline, FOptionalBool& bOnline, FOptionalString& PlayerId, FOptionalPresenceStatus& Status, FOptionalString& Description);
};