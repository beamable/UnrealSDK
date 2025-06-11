#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetStandingsRequestBody.h"

#include "GetStandingsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetStandingsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Json", DisplayName="GetStandingsRequestBody To JSON String")
	static FString GetStandingsRequestBodyToJsonString(const UGetStandingsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make GetStandingsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Max, Focus, Cycle, From, ContentId, Outer", NativeMakeFunc))
	static UGetStandingsRequestBody* Make(FString TournamentId, FOptionalInt32 Max, FOptionalInt64 Focus, FOptionalInt32 Cycle, FOptionalInt32 From, FOptionalString ContentId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Break GetStandingsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetStandingsRequestBody* Serializable, FString& TournamentId, FOptionalInt32& Max, FOptionalInt64& Focus, FOptionalInt32& Cycle, FOptionalInt32& From, FOptionalString& ContentId);
};