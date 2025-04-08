#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RemoveFromLobby.h"

#include "RemoveFromLobbyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URemoveFromLobbyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="RemoveFromLobby To JSON String")
	static FString RemoveFromLobbyToJsonString(const URemoveFromLobby* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make RemoveFromLobby", meta=(DefaultToSelf="Outer", AdvancedDisplay="PlayerId, Outer", NativeMakeFunc))
	static URemoveFromLobby* Make(FOptionalBeamGamerTag PlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break RemoveFromLobby", meta=(NativeBreakFunc))
	static void Break(const URemoveFromLobby* Serializable, FOptionalBeamGamerTag& PlayerId);
};