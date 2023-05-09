#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ThirdPartyAvailableRequestBody.h"

#include "ThirdPartyAvailableRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UThirdPartyAvailableRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ThirdPartyAvailableRequestBody To JSON String")
	static FString ThirdPartyAvailableRequestBodyToJsonString(const UThirdPartyAvailableRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ThirdPartyAvailableRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UThirdPartyAvailableRequestBody* Make(FString ThirdParty, FString Token, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ThirdPartyAvailableRequestBody", meta=(NativeBreakFunc))
	static void Break(const UThirdPartyAvailableRequestBody* Serializable, FString& ThirdParty, FString& Token);
};