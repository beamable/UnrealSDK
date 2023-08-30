#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/UpdateLobby.h"

#include "UpdateLobbyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUpdateLobbyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - UpdateLobby To JSON String")
	static FString UpdateLobbyToJsonString(const UUpdateLobby* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make UpdateLobby", meta=(DefaultToSelf="Outer", AdvancedDisplay="Name, Description, Restriction, MatchType, MaxPlayers, NewHost, Outer", NativeMakeFunc))
	static UUpdateLobby* Make(FOptionalString Name, FOptionalString Description, FOptionalString Restriction, FOptionalBeamContentId MatchType, FOptionalInt32 MaxPlayers, FOptionalString NewHost, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break UpdateLobby", meta=(NativeBreakFunc))
	static void Break(const UUpdateLobby* Serializable, FOptionalString& Name, FOptionalString& Description, FOptionalString& Restriction, FOptionalBeamContentId& MatchType, FOptionalInt32& MaxPlayers, FOptionalString& NewHost);
};