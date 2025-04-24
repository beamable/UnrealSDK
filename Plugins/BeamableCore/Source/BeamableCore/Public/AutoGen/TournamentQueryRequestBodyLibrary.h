#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TournamentQueryRequestBody.h"

#include "TournamentQueryRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTournamentQueryRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Json", DisplayName="TournamentQueryRequestBody To JSON String")
	static FString TournamentQueryRequestBodyToJsonString(const UTournamentQueryRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make TournamentQueryRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bIsRunning, ContentId, Cycle, Outer", NativeMakeFunc))
	static UTournamentQueryRequestBody* Make(FOptionalBool bIsRunning, FOptionalString ContentId, FOptionalInt32 Cycle, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Break TournamentQueryRequestBody", meta=(NativeBreakFunc))
	static void Break(const UTournamentQueryRequestBody* Serializable, FOptionalBool& bIsRunning, FOptionalString& ContentId, FOptionalInt32& Cycle);
};