#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Lobby.h"

#include "LobbyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULobbyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - Lobby To JSON String")
	static FString LobbyToJsonString(const ULobby* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make Lobby", meta=(DefaultToSelf="Outer", AdvancedDisplay="LobbyId, MatchType, Created, Name, Description, Host, Passcode, Restriction, MaxPlayers, Players, Outer", NativeMakeFunc))
	static ULobby* Make(FOptionalString LobbyId, FOptionalMatchType MatchType, FOptionalString Created, FOptionalString Name, FOptionalString Description, FOptionalString Host, FOptionalString Passcode, FOptionalLobbyRestriction Restriction, FOptionalInt32 MaxPlayers, FOptionalArrayOfLobbyPlayer Players, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break Lobby", meta=(NativeBreakFunc))
	static void Break(const ULobby* Serializable, FOptionalString& LobbyId, FOptionalMatchType& MatchType, FOptionalString& Created, FOptionalString& Name, FOptionalString& Description, FOptionalString& Host, FOptionalString& Passcode, FOptionalLobbyRestriction& Restriction, FOptionalInt32& MaxPlayers, FOptionalArrayOfLobbyPlayer& Players);
};