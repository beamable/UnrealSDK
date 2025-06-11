#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Lobby.h"

#include "LobbyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULobbyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Json", DisplayName="Lobby To JSON String")
	static FString LobbyToJsonString(const ULobby* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Make Lobby", meta=(DefaultToSelf="Outer", AdvancedDisplay="LobbyId, MatchType, Created, Name, Description, Host, Passcode, Restriction, MaxPlayers, Players, Data, Outer", NativeMakeFunc))
	static ULobby* Make(FOptionalString LobbyId, FOptionalMatchType MatchType, FOptionalDateTime Created, FOptionalString Name, FOptionalString Description, FOptionalBeamGamerTag Host, FOptionalString Passcode, FOptionalLobbyRestriction Restriction, FOptionalInt32 MaxPlayers, FOptionalArrayOfLobbyPlayer Players, FOptionalMapOfString Data, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Break Lobby", meta=(NativeBreakFunc))
	static void Break(const ULobby* Serializable, FOptionalString& LobbyId, FOptionalMatchType& MatchType, FOptionalDateTime& Created, FOptionalString& Name, FOptionalString& Description, FOptionalBeamGamerTag& Host, FOptionalString& Passcode, FOptionalLobbyRestriction& Restriction, FOptionalInt32& MaxPlayers, FOptionalArrayOfLobbyPlayer& Players, FOptionalMapOfString& Data);
};