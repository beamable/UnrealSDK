#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LobbyQueryResponse.h"

#include "LobbyQueryResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULobbyQueryResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Json", DisplayName="LobbyQueryResponse To JSON String")
	static FString LobbyQueryResponseToJsonString(const ULobbyQueryResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Make LobbyQueryResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Results, Outer", NativeMakeFunc))
	static ULobbyQueryResponse* Make(FOptionalArrayOfLobby Results, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Break LobbyQueryResponse", meta=(NativeBreakFunc))
	static void Break(const ULobbyQueryResponse* Serializable, FOptionalArrayOfLobby& Results);
};