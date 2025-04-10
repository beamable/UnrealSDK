#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RewardsRequestBody.h"

#include "RewardsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URewardsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Json", DisplayName="RewardsRequestBody To JSON String")
	static FString RewardsRequestBodyToJsonString(const URewardsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make RewardsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="TournamentId, ContentId, Outer", NativeMakeFunc))
	static URewardsRequestBody* Make(FOptionalString TournamentId, FOptionalString ContentId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Break RewardsRequestBody", meta=(NativeBreakFunc))
	static void Break(const URewardsRequestBody* Serializable, FOptionalString& TournamentId, FOptionalString& ContentId);
};