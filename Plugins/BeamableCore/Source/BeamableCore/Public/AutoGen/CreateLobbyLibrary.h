#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CreateLobby.h"

#include "CreateLobbyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCreateLobbyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - CreateLobby To JSON String")
	static FString CreateLobbyToJsonString(const UCreateLobby* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make CreateLobby", meta=(DefaultToSelf="Outer", AdvancedDisplay="Name, Description, Restriction, MatchType, PasscodeLength, MaxPlayers, PlayerTags, Outer", NativeMakeFunc))
	static UCreateLobby* Make(FOptionalString Name, FOptionalString Description, FOptionalString Restriction, FOptionalBeamContentId MatchType, FOptionalInt32 PasscodeLength, FOptionalInt32 MaxPlayers, FOptionalArrayOfTag PlayerTags, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break CreateLobby", meta=(NativeBreakFunc))
	static void Break(const UCreateLobby* Serializable, FOptionalString& Name, FOptionalString& Description, FOptionalString& Restriction, FOptionalBeamContentId& MatchType, FOptionalInt32& PasscodeLength, FOptionalInt32& MaxPlayers, FOptionalArrayOfTag& PlayerTags);
};