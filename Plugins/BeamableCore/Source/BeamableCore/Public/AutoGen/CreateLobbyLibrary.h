#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CreateLobby.h"

#include "CreateLobbyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCreateLobbyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Json", DisplayName="CreateLobby To JSON String")
	static FString CreateLobbyToJsonString(const UCreateLobby* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Make CreateLobby", meta=(DefaultToSelf="Outer", AdvancedDisplay="Name, Description, Restriction, MatchType, PasscodeLength, MaxPlayers, PlayerTags, Data, Outer", NativeMakeFunc))
	static UCreateLobby* Make(FOptionalString Name, FOptionalString Description, FOptionalLobbyRestriction Restriction, FOptionalBeamContentId MatchType, FOptionalInt32 PasscodeLength, FOptionalInt32 MaxPlayers, FOptionalArrayOfBeamTag PlayerTags, FOptionalMapOfString Data, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Break CreateLobby", meta=(NativeBreakFunc))
	static void Break(const UCreateLobby* Serializable, FOptionalString& Name, FOptionalString& Description, FOptionalLobbyRestriction& Restriction, FOptionalBeamContentId& MatchType, FOptionalInt32& PasscodeLength, FOptionalInt32& MaxPlayers, FOptionalArrayOfBeamTag& PlayerTags, FOptionalMapOfString& Data);
};