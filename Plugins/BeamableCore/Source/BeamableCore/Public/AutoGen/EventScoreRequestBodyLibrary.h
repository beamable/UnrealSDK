#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventScoreRequestBody.h"

#include "EventScoreRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventScoreRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Json", DisplayName="EventScoreRequestBody To JSON String")
	static FString EventScoreRequestBodyToJsonString(const UEventScoreRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Make EventScoreRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bIncrement, Stats, Outer", NativeMakeFunc))
	static UEventScoreRequestBody* Make(FString EventId, double Score, FOptionalBool bIncrement, FOptionalMapOfString Stats, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Break EventScoreRequestBody", meta=(NativeBreakFunc))
	static void Break(const UEventScoreRequestBody* Serializable, FString& EventId, double& Score, FOptionalBool& bIncrement, FOptionalMapOfString& Stats);
};