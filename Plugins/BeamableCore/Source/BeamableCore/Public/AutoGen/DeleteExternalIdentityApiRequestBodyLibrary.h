
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/DeleteExternalIdentityApiRequestBody.h"

#include "DeleteExternalIdentityApiRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDeleteExternalIdentityApiRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - DeleteExternalIdentityApiRequestBody To JSON String")
	static FString DeleteExternalIdentityApiRequestBodyToJsonString(const UDeleteExternalIdentityApiRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make DeleteExternalIdentityApiRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UDeleteExternalIdentityApiRequestBody* Make(FString ProviderAddress, FString UserId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break DeleteExternalIdentityApiRequestBody", meta=(NativeBreakFunc))
	static void Break(const UDeleteExternalIdentityApiRequestBody* Serializable, FString& ProviderAddress, FString& UserId);
};