#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PlayersStatusResponse.h"

#include "PlayersStatusResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPlayersStatusResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Presence|Utils|Json", DisplayName="PlayersStatusResponse To JSON String")
	static FString PlayersStatusResponseToJsonString(const UPlayersStatusResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Presence|Utils|Make/Break", DisplayName="Make PlayersStatusResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="PlayersStatus, Outer", NativeMakeFunc))
	static UPlayersStatusResponse* Make(FOptionalArrayOfOnlineStatus PlayersStatus, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Presence|Utils|Make/Break", DisplayName="Break PlayersStatusResponse", meta=(NativeBreakFunc))
	static void Break(const UPlayersStatusResponse* Serializable, FOptionalArrayOfOnlineStatus& PlayersStatus);
};