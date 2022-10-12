
#pragma once

#include "CoreMinimal.h"
#include "MatchMakingMatchesPvpResponse.h"

#include "MatchMakingMatchesPvpResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMatchMakingMatchesPvpResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize MatchMakingMatchesPvpResponse To JSON String")
	static FString MatchMakingMatchesPvpResponseToJsonString(const UMatchMakingMatchesPvpResponse* Serializable, const bool Pretty);		
};