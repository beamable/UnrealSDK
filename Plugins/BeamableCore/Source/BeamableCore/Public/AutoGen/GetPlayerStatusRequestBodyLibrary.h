#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetPlayerStatusRequestBody.h"

#include "GetPlayerStatusRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetPlayerStatusRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Json", DisplayName="GetPlayerStatusRequestBody To JSON String")
	static FString GetPlayerStatusRequestBodyToJsonString(const UGetPlayerStatusRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make GetPlayerStatusRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bHasUnclaimedRewards, ContentId, TournamentId, Outer", NativeMakeFunc))
	static UGetPlayerStatusRequestBody* Make(FOptionalBool bHasUnclaimedRewards, FOptionalString ContentId, FOptionalString TournamentId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Break GetPlayerStatusRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetPlayerStatusRequestBody* Serializable, FOptionalBool& bHasUnclaimedRewards, FOptionalString& ContentId, FOptionalString& TournamentId);
};