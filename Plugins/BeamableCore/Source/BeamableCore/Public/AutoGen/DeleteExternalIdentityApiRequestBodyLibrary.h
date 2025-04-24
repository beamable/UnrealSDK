#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/DeleteExternalIdentityApiRequestBody.h"

#include "DeleteExternalIdentityApiRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDeleteExternalIdentityApiRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="DeleteExternalIdentityApiRequestBody To JSON String")
	static FString DeleteExternalIdentityApiRequestBodyToJsonString(const UDeleteExternalIdentityApiRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make DeleteExternalIdentityApiRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="ProviderNamespace, Outer", NativeMakeFunc))
	static UDeleteExternalIdentityApiRequestBody* Make(FString ProviderService, FString UserId, FOptionalString ProviderNamespace, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break DeleteExternalIdentityApiRequestBody", meta=(NativeBreakFunc))
	static void Break(const UDeleteExternalIdentityApiRequestBody* Serializable, FString& ProviderService, FString& UserId, FOptionalString& ProviderNamespace);
};