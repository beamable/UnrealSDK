#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetStandingsResponse.h"

#include "GetStandingsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetStandingsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetStandingsResponse To JSON String")
	static FString GetStandingsResponseToJsonString(const UGetStandingsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetStandingsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Me, Outer", NativeMakeFunc))
	static UGetStandingsResponse* Make(TArray<UTournamentEntry*> Entries, FOptionalTournamentEntry Me, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetStandingsResponse", meta=(NativeBreakFunc))
	static void Break(const UGetStandingsResponse* Serializable, TArray<UTournamentEntry*>& Entries, FOptionalTournamentEntry& Me);
};