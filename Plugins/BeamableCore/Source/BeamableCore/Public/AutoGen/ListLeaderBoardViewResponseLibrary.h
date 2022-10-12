
#pragma once

#include "CoreMinimal.h"
#include "ListLeaderBoardViewResponse.h"

#include "ListLeaderBoardViewResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UListLeaderBoardViewResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ListLeaderBoardViewResponse To JSON String")
	static FString ListLeaderBoardViewResponseToJsonString(const UListLeaderBoardViewResponse* Serializable, const bool Pretty);		
};