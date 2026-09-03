#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/BeamballMsUpdateFromDiscordResponse.h"

#include "BeamballMsUpdateFromDiscordResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamballMsUpdateFromDiscordResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Json", DisplayName="BeamballMsUpdateFromDiscordResponse To JSON String")
	static FString BeamballMsUpdateFromDiscordResponseToJsonString(const UBeamballMsUpdateFromDiscordResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Make BeamballMsUpdateFromDiscordResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBeamballMsUpdateFromDiscordResponse* Make(bool bValue, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Break BeamballMsUpdateFromDiscordResponse", meta=(NativeBreakFunc))
	static void Break(const UBeamballMsUpdateFromDiscordResponse* Serializable, bool& bValue);
};