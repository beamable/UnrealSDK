#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TournamentQueryResponse.h"

#include "TournamentQueryResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTournamentQueryResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - TournamentQueryResponse To JSON String")
	static FString TournamentQueryResponseToJsonString(const UTournamentQueryResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make TournamentQueryResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UTournamentQueryResponse* Make(TArray<UTournamentClientView*> Tournaments, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break TournamentQueryResponse", meta=(NativeBreakFunc))
	static void Break(const UTournamentQueryResponse* Serializable, TArray<UTournamentClientView*>& Tournaments);
};