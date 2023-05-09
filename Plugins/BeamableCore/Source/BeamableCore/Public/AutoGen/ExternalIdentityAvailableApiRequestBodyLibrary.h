#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ExternalIdentityAvailableApiRequestBody.h"

#include "ExternalIdentityAvailableApiRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UExternalIdentityAvailableApiRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ExternalIdentityAvailableApiRequestBody To JSON String")
	static FString ExternalIdentityAvailableApiRequestBodyToJsonString(const UExternalIdentityAvailableApiRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ExternalIdentityAvailableApiRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="ProviderNamespace, Outer", NativeMakeFunc))
	static UExternalIdentityAvailableApiRequestBody* Make(FString ProviderService, FString UserId, FOptionalString ProviderNamespace, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ExternalIdentityAvailableApiRequestBody", meta=(NativeBreakFunc))
	static void Break(const UExternalIdentityAvailableApiRequestBody* Serializable, FString& ProviderService, FString& UserId, FOptionalString& ProviderNamespace);
};