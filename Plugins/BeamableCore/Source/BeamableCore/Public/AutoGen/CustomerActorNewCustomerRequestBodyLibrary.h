#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CustomerActorNewCustomerRequestBody.h"

#include "CustomerActorNewCustomerRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCustomerActorNewCustomerRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="CustomerActorNewCustomerRequestBody To JSON String")
	static FString CustomerActorNewCustomerRequestBodyToJsonString(const UCustomerActorNewCustomerRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make CustomerActorNewCustomerRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bHierarchy, CustomerName, Alias, Outer", NativeMakeFunc))
	static UCustomerActorNewCustomerRequestBody* Make(FString RealmName, FString Email, FString Password, FOptionalBool bHierarchy, FOptionalString CustomerName, FOptionalString Alias, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break CustomerActorNewCustomerRequestBody", meta=(NativeBreakFunc))
	static void Break(const UCustomerActorNewCustomerRequestBody* Serializable, FString& RealmName, FString& Email, FString& Password, FOptionalBool& bHierarchy, FOptionalString& CustomerName, FOptionalString& Alias);
};