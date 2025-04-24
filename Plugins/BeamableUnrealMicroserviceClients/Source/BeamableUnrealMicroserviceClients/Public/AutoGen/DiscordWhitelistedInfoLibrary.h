#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DiscordWhitelistedInfo.h"

#include "DiscordWhitelistedInfoLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UDiscordWhitelistedInfoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|DiscordSampleMs|Utils|Json", DisplayName="DiscordWhitelistedInfo To JSON String")
	static FString DiscordWhitelistedInfoToJsonString(const UDiscordWhitelistedInfo* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|DiscordSampleMs|Utils|Make/Break", DisplayName="Make DiscordWhitelistedInfo", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UDiscordWhitelistedInfo* Make(bool bMatchmakingDiscordWhitelisted, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|DiscordSampleMs|Utils|Make/Break", DisplayName="Break DiscordWhitelistedInfo", meta=(NativeBreakFunc))
	static void Break(const UDiscordWhitelistedInfo* Serializable, bool& bMatchmakingDiscordWhitelisted);
};