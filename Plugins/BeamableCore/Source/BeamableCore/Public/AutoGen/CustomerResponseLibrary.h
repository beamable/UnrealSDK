#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CustomerResponse.h"

#include "CustomerResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCustomerResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="CustomerResponse To JSON String")
	static FString CustomerResponseToJsonString(const UCustomerResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make CustomerResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCustomerResponse* Make(UCustomer* Customer, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break CustomerResponse", meta=(NativeBreakFunc))
	static void Break(const UCustomerResponse* Serializable, UCustomer*& Customer);
};