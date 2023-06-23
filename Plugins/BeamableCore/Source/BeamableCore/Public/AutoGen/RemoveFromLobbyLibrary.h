#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RemoveFromLobby.h"

#include "RemoveFromLobbyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URemoveFromLobbyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - RemoveFromLobby To JSON String")
	static FString RemoveFromLobbyToJsonString(const URemoveFromLobby* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make RemoveFromLobby", meta=(DefaultToSelf="Outer", AdvancedDisplay="PlayerId, Outer", NativeMakeFunc))
	static URemoveFromLobby* Make(FOptionalString PlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break RemoveFromLobby", meta=(NativeBreakFunc))
	static void Break(const URemoveFromLobby* Serializable, FOptionalString& PlayerId);
};