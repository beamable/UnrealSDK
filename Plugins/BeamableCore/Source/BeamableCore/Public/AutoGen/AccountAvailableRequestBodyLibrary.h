#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AccountAvailableRequestBody.h"

#include "AccountAvailableRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAccountAvailableRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="AccountAvailableRequestBody To JSON String")
	static FString AccountAvailableRequestBodyToJsonString(const UAccountAvailableRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make AccountAvailableRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAccountAvailableRequestBody* Make(FString Email, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break AccountAvailableRequestBody", meta=(NativeBreakFunc))
	static void Break(const UAccountAvailableRequestBody* Serializable, FString& Email);
};