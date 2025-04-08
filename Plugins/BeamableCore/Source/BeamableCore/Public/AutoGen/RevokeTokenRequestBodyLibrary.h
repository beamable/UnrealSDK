#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RevokeTokenRequestBody.h"

#include "RevokeTokenRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URevokeTokenRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="RevokeTokenRequestBody To JSON String")
	static FString RevokeTokenRequestBodyToJsonString(const URevokeTokenRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make RevokeTokenRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URevokeTokenRequestBody* Make(FString Token, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break RevokeTokenRequestBody", meta=(NativeBreakFunc))
	static void Break(const URevokeTokenRequestBody* Serializable, FString& Token);
};