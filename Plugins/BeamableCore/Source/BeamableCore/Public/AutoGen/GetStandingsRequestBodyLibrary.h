#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetStandingsRequestBody.h"

#include "GetStandingsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetStandingsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetStandingsRequestBody To JSON String")
	static FString GetStandingsRequestBodyToJsonString(const UGetStandingsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetStandingsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Max, Focus, Cycle, From, Outer", NativeMakeFunc))
	static UGetStandingsRequestBody* Make(FString TournamentId, FOptionalInt32 Max, FOptionalInt64 Focus, FOptionalInt32 Cycle, FOptionalInt32 From, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetStandingsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetStandingsRequestBody* Serializable, FString& TournamentId, FOptionalInt32& Max, FOptionalInt64& Focus, FOptionalInt32& Cycle, FOptionalInt32& From);
};