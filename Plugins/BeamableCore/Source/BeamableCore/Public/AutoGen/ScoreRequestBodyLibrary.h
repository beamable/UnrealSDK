#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/ScoreRequestBody.h"

#include "ScoreRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UScoreRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ScoreRequestBody To JSON String")
	static FString ScoreRequestBodyToJsonString(const UScoreRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ScoreRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bIncrement, ContentId, Stats, Outer", NativeMakeFunc))
	static UScoreRequestBody* Make(FString TournamentId, double Score, int64 PlayerId, FOptionalBool bIncrement, FOptionalString ContentId, FOptionalMapOfString Stats, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ScoreRequestBody", meta=(NativeBreakFunc))
	static void Break(const UScoreRequestBody* Serializable, FString& TournamentId, double& Score, int64& PlayerId, FOptionalBool& bIncrement, FOptionalString& ContentId, FOptionalMapOfString& Stats);
};