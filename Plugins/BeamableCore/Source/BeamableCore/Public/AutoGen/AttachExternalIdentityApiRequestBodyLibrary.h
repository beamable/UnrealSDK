#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/AttachExternalIdentityApiRequestBody.h"

#include "AttachExternalIdentityApiRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAttachExternalIdentityApiRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - AttachExternalIdentityApiRequestBody To JSON String")
	static FString AttachExternalIdentityApiRequestBodyToJsonString(const UAttachExternalIdentityApiRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make AttachExternalIdentityApiRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="ChallengeSolution, ProviderNamespace, Outer", NativeMakeFunc))
	static UAttachExternalIdentityApiRequestBody* Make(FString ProviderService, FString ExternalToken, FOptionalChallengeSolution ChallengeSolution, FOptionalString ProviderNamespace, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break AttachExternalIdentityApiRequestBody", meta=(NativeBreakFunc))
	static void Break(const UAttachExternalIdentityApiRequestBody* Serializable, FString& ProviderService, FString& ExternalToken, FOptionalChallengeSolution& ChallengeSolution, FOptionalString& ProviderNamespace);
};