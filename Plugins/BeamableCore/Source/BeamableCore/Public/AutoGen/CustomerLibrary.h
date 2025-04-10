#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Customer.h"

#include "CustomerLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCustomerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="Customer To JSON String")
	static FString CustomerToJsonString(const UCustomer* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make Customer", meta=(DefaultToSelf="Outer", AdvancedDisplay="ActivationStatus, PaymentStatus, Image, Contact, Alias, Updated, CrmLink, Created, Outer", NativeMakeFunc))
	static UCustomer* Make(FString Name, FBeamCid Cid, TArray<UProject*> Projects, TArray<URealmsBasicAccount*> Accounts, FOptionalString ActivationStatus, FOptionalString PaymentStatus, FOptionalString Image, FOptionalString Contact, FOptionalString Alias, FOptionalInt64 Updated, FOptionalString CrmLink, FOptionalInt64 Created, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break Customer", meta=(NativeBreakFunc))
	static void Break(const UCustomer* Serializable, FString& Name, FBeamCid& Cid, TArray<UProject*>& Projects, TArray<URealmsBasicAccount*>& Accounts, FOptionalString& ActivationStatus, FOptionalString& PaymentStatus, FOptionalString& Image, FOptionalString& Contact, FOptionalString& Alias, FOptionalInt64& Updated, FOptionalString& CrmLink, FOptionalInt64& Created);
};