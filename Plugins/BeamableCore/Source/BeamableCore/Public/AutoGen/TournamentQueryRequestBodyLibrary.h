#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TournamentQueryRequestBody.h"

#include "TournamentQueryRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTournamentQueryRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - TournamentQueryRequestBody To JSON String")
	static FString TournamentQueryRequestBodyToJsonString(const UTournamentQueryRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make TournamentQueryRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bIsRunning, ContentId, Cycle, Outer", NativeMakeFunc))
	static UTournamentQueryRequestBody* Make(FOptionalBool bIsRunning, FOptionalString ContentId, FOptionalInt32 Cycle, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break TournamentQueryRequestBody", meta=(NativeBreakFunc))
	static void Break(const UTournamentQueryRequestBody* Serializable, FOptionalBool& bIsRunning, FOptionalString& ContentId, FOptionalInt32& Cycle);
};