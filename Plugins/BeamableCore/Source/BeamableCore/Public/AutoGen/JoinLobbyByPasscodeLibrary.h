#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/JoinLobbyByPasscode.h"

#include "JoinLobbyByPasscodeLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UJoinLobbyByPasscodeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - JoinLobbyByPasscode To JSON String")
	static FString JoinLobbyByPasscodeToJsonString(const UJoinLobbyByPasscode* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make JoinLobbyByPasscode", meta=(DefaultToSelf="Outer", AdvancedDisplay="Passcode, Tags, Outer", NativeMakeFunc))
	static UJoinLobbyByPasscode* Make(FOptionalString Passcode, FOptionalArrayOfTag Tags, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break JoinLobbyByPasscode", meta=(NativeBreakFunc))
	static void Break(const UJoinLobbyByPasscode* Serializable, FOptionalString& Passcode, FOptionalArrayOfTag& Tags);
};