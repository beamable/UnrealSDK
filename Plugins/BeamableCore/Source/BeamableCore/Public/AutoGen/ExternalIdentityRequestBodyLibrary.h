
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/ExternalIdentityRequestBody.h"

#include "ExternalIdentityRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UExternalIdentityRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ExternalIdentityRequestBody To JSON String")
	static FString ExternalIdentityRequestBodyToJsonString(const UExternalIdentityRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ExternalIdentityRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="ChallengeSolution, Outer", NativeMakeFunc))
	static UExternalIdentityRequestBody* Make(FString ProviderAddress, FString ExternalToken, FOptionalChallengeSolution ChallengeSolution, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ExternalIdentityRequestBody", meta=(NativeBreakFunc))
	static void Break(const UExternalIdentityRequestBody* Serializable, FString& ProviderAddress, FString& ExternalToken, FOptionalChallengeSolution& ChallengeSolution);
};