
#pragma once

#include "CoreMinimal.h"
#include "LeaderBoardView.h"

#include "LeaderBoardViewLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaderBoardViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaderBoardView To JSON String")
	static FString LeaderBoardViewToJsonString(const ULeaderBoardView* Serializable, const bool Pretty);		
};