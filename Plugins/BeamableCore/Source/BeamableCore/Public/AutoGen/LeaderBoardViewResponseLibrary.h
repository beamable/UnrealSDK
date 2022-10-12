
#pragma once

#include "CoreMinimal.h"
#include "LeaderBoardViewResponse.h"

#include "LeaderBoardViewResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderBoardViewResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderBoardViewResponse To JSON String")
	static FString LeaderBoardViewResponseToJsonString(const ULeaderBoardViewResponse* Serializable, const bool Pretty);		
};