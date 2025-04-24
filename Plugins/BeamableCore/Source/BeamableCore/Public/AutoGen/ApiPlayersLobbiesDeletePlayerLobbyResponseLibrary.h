#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ApiPlayersLobbiesDeletePlayerLobbyResponse.h"

#include "ApiPlayersLobbiesDeletePlayerLobbyResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UApiPlayersLobbiesDeletePlayerLobbyResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|PlayerLobby|Utils|Json", DisplayName="ApiPlayersLobbiesDeletePlayerLobbyResponse To JSON String")
	static FString ApiPlayersLobbiesDeletePlayerLobbyResponseToJsonString(const UApiPlayersLobbiesDeletePlayerLobbyResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|PlayerLobby|Utils|Make/Break", DisplayName="Make ApiPlayersLobbiesDeletePlayerLobbyResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UApiPlayersLobbiesDeletePlayerLobbyResponse* Make(UObject* Outer);

	
};