#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/UpdateLobby.h"

#include "UpdateLobbyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUpdateLobbyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Json", DisplayName="UpdateLobby To JSON String")
	static FString UpdateLobbyToJsonString(const UUpdateLobby* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Make UpdateLobby", meta=(DefaultToSelf="Outer", AdvancedDisplay="Name, Description, Restriction, MatchType, MaxPlayers, NewHost, Data, Outer", NativeMakeFunc))
	static UUpdateLobby* Make(FOptionalString Name, FOptionalString Description, FOptionalLobbyRestriction Restriction, FOptionalBeamContentId MatchType, FOptionalInt32 MaxPlayers, FOptionalString NewHost, FOptionalUpdateData Data, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Break UpdateLobby", meta=(NativeBreakFunc))
	static void Break(const UUpdateLobby* Serializable, FOptionalString& Name, FOptionalString& Description, FOptionalLobbyRestriction& Restriction, FOptionalBeamContentId& MatchType, FOptionalInt32& MaxPlayers, FOptionalString& NewHost, FOptionalUpdateData& Data);
};