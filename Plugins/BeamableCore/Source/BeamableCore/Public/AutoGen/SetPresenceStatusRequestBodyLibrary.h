#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SetPresenceStatusRequestBody.h"

#include "SetPresenceStatusRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USetPresenceStatusRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Player|Utils|Json", DisplayName="SetPresenceStatusRequestBody To JSON String")
	static FString SetPresenceStatusRequestBodyToJsonString(const USetPresenceStatusRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Player|Utils|Make/Break", DisplayName="Make SetPresenceStatusRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Status, Description, Outer", NativeMakeFunc))
	static USetPresenceStatusRequestBody* Make(FOptionalPresenceStatus Status, FOptionalString Description, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Player|Utils|Make/Break", DisplayName="Break SetPresenceStatusRequestBody", meta=(NativeBreakFunc))
	static void Break(const USetPresenceStatusRequestBody* Serializable, FOptionalPresenceStatus& Status, FOptionalString& Description);
};