#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetTokenRequestBody.h"

#include "GetTokenRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetTokenRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="GetTokenRequestBody To JSON String")
	static FString GetTokenRequestBodyToJsonString(const UGetTokenRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make GetTokenRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetTokenRequestBody* Make(FString Token, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break GetTokenRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetTokenRequestBody* Serializable, FString& Token);
};