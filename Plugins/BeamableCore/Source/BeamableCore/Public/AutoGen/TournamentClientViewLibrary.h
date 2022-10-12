
#pragma once

#include "CoreMinimal.h"
#include "TournamentClientView.h"

#include "TournamentClientViewLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UTournamentClientViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize TournamentClientView To JSON String")
	static FString TournamentClientViewToJsonString(const UTournamentClientView* Serializable, const bool Pretty);		
};