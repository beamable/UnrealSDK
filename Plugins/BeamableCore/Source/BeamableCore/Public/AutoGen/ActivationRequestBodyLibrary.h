#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ActivationRequestBody.h"

#include "ActivationRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UActivationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="ActivationRequestBody To JSON String")
	static FString ActivationRequestBodyToJsonString(const UActivationRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make ActivationRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UActivationRequestBody* Make(FString Token, int64 Cid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break ActivationRequestBody", meta=(NativeBreakFunc))
	static void Break(const UActivationRequestBody* Serializable, FString& Token, int64& Cid);
};