#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LobbyPlayer.h"

#include "LobbyPlayerLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULobbyPlayerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Json", DisplayName="LobbyPlayer To JSON String")
	static FString LobbyPlayerToJsonString(const ULobbyPlayer* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Make LobbyPlayer", meta=(DefaultToSelf="Outer", AdvancedDisplay="PlayerId, Joined, Tags, Outer", NativeMakeFunc))
	static ULobbyPlayer* Make(FOptionalBeamGamerTag PlayerId, FOptionalDateTime Joined, FOptionalArrayOfBeamTag Tags, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Break LobbyPlayer", meta=(NativeBreakFunc))
	static void Break(const ULobbyPlayer* Serializable, FOptionalBeamGamerTag& PlayerId, FOptionalDateTime& Joined, FOptionalArrayOfBeamTag& Tags);
};