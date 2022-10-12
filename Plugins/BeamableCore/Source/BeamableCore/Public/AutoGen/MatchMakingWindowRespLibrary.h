
#pragma once

#include "CoreMinimal.h"
#include "MatchMakingWindowResp.h"

#include "MatchMakingWindowRespLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMatchMakingWindowRespLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize MatchMakingWindowResp To JSON String")
	static FString MatchMakingWindowRespToJsonString(const UMatchMakingWindowResp* Serializable, const bool Pretty);		
};