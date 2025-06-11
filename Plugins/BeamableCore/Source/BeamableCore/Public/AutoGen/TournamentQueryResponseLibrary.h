#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TournamentQueryResponse.h"

#include "TournamentQueryResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTournamentQueryResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Json", DisplayName="TournamentQueryResponse To JSON String")
	static FString TournamentQueryResponseToJsonString(const UTournamentQueryResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make TournamentQueryResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UTournamentQueryResponse* Make(TArray<UTournamentClientView*> Tournaments, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Break TournamentQueryResponse", meta=(NativeBreakFunc))
	static void Break(const UTournamentQueryResponse* Serializable, TArray<UTournamentClientView*>& Tournaments);
};