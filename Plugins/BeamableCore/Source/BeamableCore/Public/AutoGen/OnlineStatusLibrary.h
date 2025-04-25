#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/OnlineStatus.h"

#include "OnlineStatusLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UOnlineStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Presence|Utils|Json", DisplayName="OnlineStatus To JSON String")
	static FString OnlineStatusToJsonString(const UOnlineStatus* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Presence|Utils|Make/Break", DisplayName="Make OnlineStatus", meta=(DefaultToSelf="Outer", AdvancedDisplay="LastOnline, bOnline, PlayerId, Status, Description, Outer", NativeMakeFunc))
	static UOnlineStatus* Make(FOptionalDateTime LastOnline, FOptionalBool bOnline, FOptionalBeamGamerTag PlayerId, FOptionalPresenceStatus Status, FOptionalString Description, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Presence|Utils|Make/Break", DisplayName="Break OnlineStatus", meta=(NativeBreakFunc))
	static void Break(const UOnlineStatus* Serializable, FOptionalDateTime& LastOnline, FOptionalBool& bOnline, FOptionalBeamGamerTag& PlayerId, FOptionalPresenceStatus& Status, FOptionalString& Description);
};