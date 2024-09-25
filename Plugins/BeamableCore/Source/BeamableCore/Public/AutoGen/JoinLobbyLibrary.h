#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/JoinLobby.h"

#include "JoinLobbyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UJoinLobbyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - JoinLobby To JSON String")
	static FString JoinLobbyToJsonString(const UJoinLobby* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make JoinLobby", meta=(DefaultToSelf="Outer", AdvancedDisplay="Passcode, Tags, Outer", NativeMakeFunc))
	static UJoinLobby* Make(FOptionalString Passcode, FOptionalArrayOfBeamTag Tags, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break JoinLobby", meta=(NativeBreakFunc))
	static void Break(const UJoinLobby* Serializable, FOptionalString& Passcode, FOptionalArrayOfBeamTag& Tags);
};