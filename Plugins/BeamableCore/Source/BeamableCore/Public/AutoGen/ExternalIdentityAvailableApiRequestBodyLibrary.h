#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ExternalIdentityAvailableApiRequestBody.h"

#include "ExternalIdentityAvailableApiRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UExternalIdentityAvailableApiRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="ExternalIdentityAvailableApiRequestBody To JSON String")
	static FString ExternalIdentityAvailableApiRequestBodyToJsonString(const UExternalIdentityAvailableApiRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make ExternalIdentityAvailableApiRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="ProviderNamespace, Outer", NativeMakeFunc))
	static UExternalIdentityAvailableApiRequestBody* Make(FString ProviderService, FString UserId, FOptionalString ProviderNamespace, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break ExternalIdentityAvailableApiRequestBody", meta=(NativeBreakFunc))
	static void Break(const UExternalIdentityAvailableApiRequestBody* Serializable, FString& ProviderService, FString& UserId, FOptionalString& ProviderNamespace);
};