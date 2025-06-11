#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/JoinRequestBody.h"

#include "JoinRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UJoinRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Json", DisplayName="JoinRequestBody To JSON String")
	static FString JoinRequestBodyToJsonString(const UJoinRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make JoinRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="ContentId, Outer", NativeMakeFunc))
	static UJoinRequestBody* Make(FString TournamentId, FOptionalString ContentId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Break JoinRequestBody", meta=(NativeBreakFunc))
	static void Break(const UJoinRequestBody* Serializable, FString& TournamentId, FOptionalString& ContentId);
};