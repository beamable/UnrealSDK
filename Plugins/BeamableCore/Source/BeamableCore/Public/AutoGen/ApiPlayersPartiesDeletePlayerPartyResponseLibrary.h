#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ApiPlayersPartiesDeletePlayerPartyResponse.h"

#include "ApiPlayersPartiesDeletePlayerPartyResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UApiPlayersPartiesDeletePlayerPartyResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ApiPlayersPartiesDeletePlayerPartyResponse To JSON String")
	static FString ApiPlayersPartiesDeletePlayerPartyResponseToJsonString(const UApiPlayersPartiesDeletePlayerPartyResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ApiPlayersPartiesDeletePlayerPartyResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UApiPlayersPartiesDeletePlayerPartyResponse* Make(UObject* Outer);

	
};