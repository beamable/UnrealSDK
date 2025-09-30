#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CustomerActorCustomer.h"

#include "CustomerActorCustomerLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCustomerActorCustomerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="CustomerActorCustomer To JSON String")
	static FString CustomerActorCustomerToJsonString(const UCustomerActorCustomer* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make CustomerActorCustomer", meta=(DefaultToSelf="Outer", AdvancedDisplay="Alias, PaymentStatus, ActivationStatus, Contact, Created, Updated, Realms, Outer", NativeMakeFunc))
	static UCustomerActorCustomer* Make(int64 CustomerId, FString Name, FOptionalString Alias, FOptionalPaymentStatus PaymentStatus, FOptionalActivationStatus ActivationStatus, FOptionalString Contact, FOptionalInt64 Created, FOptionalInt64 Updated, FOptionalArrayOfRealm Realms, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break CustomerActorCustomer", meta=(NativeBreakFunc))
	static void Break(const UCustomerActorCustomer* Serializable, int64& CustomerId, FString& Name, FOptionalString& Alias, FOptionalPaymentStatus& PaymentStatus, FOptionalActivationStatus& ActivationStatus, FOptionalString& Contact, FOptionalInt64& Created, FOptionalInt64& Updated, FOptionalArrayOfRealm& Realms);
};