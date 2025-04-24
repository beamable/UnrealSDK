#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DiscordSampleMsUpdateFromDiscordResponse.h"

#include "DiscordSampleMsUpdateFromDiscordResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UDiscordSampleMsUpdateFromDiscordResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|DiscordSampleMs|Utils|Json", DisplayName="DiscordSampleMsUpdateFromDiscordResponse To JSON String")
	static FString DiscordSampleMsUpdateFromDiscordResponseToJsonString(const UDiscordSampleMsUpdateFromDiscordResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|DiscordSampleMs|Utils|Make/Break", DisplayName="Make DiscordSampleMsUpdateFromDiscordResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UDiscordSampleMsUpdateFromDiscordResponse* Make(bool bValue, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|DiscordSampleMs|Utils|Make/Break", DisplayName="Break DiscordSampleMsUpdateFromDiscordResponse", meta=(NativeBreakFunc))
	static void Break(const UDiscordSampleMsUpdateFromDiscordResponse* Serializable, bool& bValue);
};