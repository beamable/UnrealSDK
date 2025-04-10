#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ThirdPartyAvailableRequestBody.h"

#include "ThirdPartyAvailableRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UThirdPartyAvailableRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|4 - Json", DisplayName="ThirdPartyAvailableRequestBody To JSON String")
	static FString ThirdPartyAvailableRequestBodyToJsonString(const UThirdPartyAvailableRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|3 - Backend", DisplayName="Make ThirdPartyAvailableRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UThirdPartyAvailableRequestBody* Make(FString ThirdParty, FString Token, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|3 - Backend", DisplayName="Break ThirdPartyAvailableRequestBody", meta=(NativeBreakFunc))
	static void Break(const UThirdPartyAvailableRequestBody* Serializable, FString& ThirdParty, FString& Token);
};