#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicNewCustomerRequestBody.h"

#include "RealmsBasicNewCustomerRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmsBasicNewCustomerRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="RealmsBasicNewCustomerRequestBody To JSON String")
	static FString RealmsBasicNewCustomerRequestBodyToJsonString(const URealmsBasicNewCustomerRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make RealmsBasicNewCustomerRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bHierarchy, CustomerName, Alias, Outer", NativeMakeFunc))
	static URealmsBasicNewCustomerRequestBody* Make(FString ProjectName, FString Email, FString Password, FOptionalBool bHierarchy, FOptionalString CustomerName, FOptionalString Alias, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break RealmsBasicNewCustomerRequestBody", meta=(NativeBreakFunc))
	static void Break(const URealmsBasicNewCustomerRequestBody* Serializable, FString& ProjectName, FString& Email, FString& Password, FOptionalBool& bHierarchy, FOptionalString& CustomerName, FOptionalString& Alias);
};