#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SetLobbyResponse.h"

#include "SetLobbyResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USetLobbyResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Json", DisplayName="SetLobbyResponse To JSON String")
	static FString SetLobbyResponseToJsonString(const USetLobbyResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Make SetLobbyResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="LobbyId, Outer", NativeMakeFunc))
	static USetLobbyResponse* Make(FOptionalString LobbyId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Break SetLobbyResponse", meta=(NativeBreakFunc))
	static void Break(const USetLobbyResponse* Serializable, FOptionalString& LobbyId);
};