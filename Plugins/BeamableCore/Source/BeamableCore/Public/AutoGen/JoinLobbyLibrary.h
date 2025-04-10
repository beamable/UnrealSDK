#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/JoinLobby.h"

#include "JoinLobbyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UJoinLobbyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|4 - Json", DisplayName="JoinLobby To JSON String")
	static FString JoinLobbyToJsonString(const UJoinLobby* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|3 - Backend", DisplayName="Make JoinLobby", meta=(DefaultToSelf="Outer", AdvancedDisplay="Passcode, Tags, Outer", NativeMakeFunc))
	static UJoinLobby* Make(FOptionalString Passcode, FOptionalArrayOfBeamTag Tags, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|3 - Backend", DisplayName="Break JoinLobby", meta=(NativeBreakFunc))
	static void Break(const UJoinLobby* Serializable, FOptionalString& Passcode, FOptionalArrayOfBeamTag& Tags);
};