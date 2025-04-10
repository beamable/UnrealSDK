#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AdminGetPlayerStatusRequestBody.h"

#include "AdminGetPlayerStatusRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAdminGetPlayerStatusRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Json", DisplayName="AdminGetPlayerStatusRequestBody To JSON String")
	static FString AdminGetPlayerStatusRequestBodyToJsonString(const UAdminGetPlayerStatusRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make AdminGetPlayerStatusRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bHasUnclaimedRewards, TournamentId, ContentId, Outer", NativeMakeFunc))
	static UAdminGetPlayerStatusRequestBody* Make(int64 PlayerId, FOptionalBool bHasUnclaimedRewards, FOptionalString TournamentId, FOptionalString ContentId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Break AdminGetPlayerStatusRequestBody", meta=(NativeBreakFunc))
	static void Break(const UAdminGetPlayerStatusRequestBody* Serializable, int64& PlayerId, FOptionalBool& bHasUnclaimedRewards, FOptionalString& TournamentId, FOptionalString& ContentId);
};