#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ApiLobbiesServerPostLobbyResponse.h"

#include "ApiLobbiesServerPostLobbyResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UApiLobbiesServerPostLobbyResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|4 - Json", DisplayName="ApiLobbiesServerPostLobbyResponse To JSON String")
	static FString ApiLobbiesServerPostLobbyResponseToJsonString(const UApiLobbiesServerPostLobbyResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|3 - Backend", DisplayName="Make ApiLobbiesServerPostLobbyResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UApiLobbiesServerPostLobbyResponse* Make(UObject* Outer);

	
};