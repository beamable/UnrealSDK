#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CreateFederatedGameServer.h"

#include "CreateFederatedGameServerLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCreateFederatedGameServerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Json", DisplayName="CreateFederatedGameServer To JSON String")
	static FString CreateFederatedGameServerToJsonString(const UCreateFederatedGameServer* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Make CreateFederatedGameServer", meta=(DefaultToSelf="Outer", AdvancedDisplay="MatchType, Outer", NativeMakeFunc))
	static UCreateFederatedGameServer* Make(FOptionalBeamContentId MatchType, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Break CreateFederatedGameServer", meta=(NativeBreakFunc))
	static void Break(const UCreateFederatedGameServer* Serializable, FOptionalBeamContentId& MatchType);
};