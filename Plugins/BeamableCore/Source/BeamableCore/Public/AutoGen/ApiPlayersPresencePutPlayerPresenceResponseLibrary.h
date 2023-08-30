#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ApiPlayersPresencePutPlayerPresenceResponse.h"

#include "ApiPlayersPresencePutPlayerPresenceResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UApiPlayersPresencePutPlayerPresenceResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ApiPlayersPresencePutPlayerPresenceResponse To JSON String")
	static FString ApiPlayersPresencePutPlayerPresenceResponseToJsonString(const UApiPlayersPresencePutPlayerPresenceResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ApiPlayersPresencePutPlayerPresenceResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UApiPlayersPresencePutPlayerPresenceResponse* Make(UObject* Outer);

	
};