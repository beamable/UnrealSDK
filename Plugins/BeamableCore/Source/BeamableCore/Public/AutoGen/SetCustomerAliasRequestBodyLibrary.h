#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SetCustomerAliasRequestBody.h"

#include "SetCustomerAliasRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USetCustomerAliasRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="SetCustomerAliasRequestBody To JSON String")
	static FString SetCustomerAliasRequestBodyToJsonString(const USetCustomerAliasRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make SetCustomerAliasRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USetCustomerAliasRequestBody* Make(FString Alias, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break SetCustomerAliasRequestBody", meta=(NativeBreakFunc))
	static void Break(const USetCustomerAliasRequestBody* Serializable, FString& Alias);
};