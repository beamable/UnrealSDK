
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/ExternalIdentity.h"

#include "ExternalIdentityLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UExternalIdentityLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ExternalIdentity To JSON String")
	static FString ExternalIdentityToJsonString(const UExternalIdentity* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ExternalIdentity", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UExternalIdentity* Make(FString ProviderAddress, FString UserId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ExternalIdentity", meta=(NativeBreakFunc))
	static void Break(const UExternalIdentity* Serializable, FString& ProviderAddress, FString& UserId);
};