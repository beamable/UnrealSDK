#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CustomerActorCustomersResponse.h"

#include "CustomerActorCustomersResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCustomerActorCustomersResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="CustomerActorCustomersResponse To JSON String")
	static FString CustomerActorCustomersResponseToJsonString(const UCustomerActorCustomersResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make CustomerActorCustomersResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Customers, Outer", NativeMakeFunc))
	static UCustomerActorCustomersResponse* Make(FOptionalArrayOfCustomerActorCustomer Customers, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break CustomerActorCustomersResponse", meta=(NativeBreakFunc))
	static void Break(const UCustomerActorCustomersResponse* Serializable, FOptionalArrayOfCustomerActorCustomer& Customers);
};