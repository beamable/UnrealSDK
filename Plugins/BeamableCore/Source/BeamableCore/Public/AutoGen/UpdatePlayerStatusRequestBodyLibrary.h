#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/UpdatePlayerStatusRequestBody.h"

#include "UpdatePlayerStatusRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUpdatePlayerStatusRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Json", DisplayName="UpdatePlayerStatusRequestBody To JSON String")
	static FString UpdatePlayerStatusRequestBodyToJsonString(const UUpdatePlayerStatusRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make UpdatePlayerStatusRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UUpdatePlayerStatusRequestBody* Make(int64 PlayerId, FString TournamentId, UPlayerStatusUpdate* Update, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Break UpdatePlayerStatusRequestBody", meta=(NativeBreakFunc))
	static void Break(const UUpdatePlayerStatusRequestBody* Serializable, int64& PlayerId, FString& TournamentId, UPlayerStatusUpdate*& Update);
};