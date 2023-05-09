#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/JoinRequestBody.h"

#include "JoinRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UJoinRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - JoinRequestBody To JSON String")
	static FString JoinRequestBodyToJsonString(const UJoinRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make JoinRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UJoinRequestBody* Make(FString TournamentId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break JoinRequestBody", meta=(NativeBreakFunc))
	static void Break(const UJoinRequestBody* Serializable, FString& TournamentId);
};