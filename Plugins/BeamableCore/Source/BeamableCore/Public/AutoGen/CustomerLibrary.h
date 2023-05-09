#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Customer.h"

#include "CustomerLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCustomerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - Customer To JSON String")
	static FString CustomerToJsonString(const UCustomer* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make Customer", meta=(DefaultToSelf="Outer", AdvancedDisplay="PaymentStatus, Image, Contact, Alias, Updated, CrmLink, Created, Outer", NativeMakeFunc))
	static UCustomer* Make(FString Name, FBeamCid Cid, TArray<UProject*> Projects, TArray<URealmsBasicAccount*> Accounts, FOptionalString PaymentStatus, FOptionalString Image, FOptionalString Contact, FOptionalString Alias, FOptionalInt64 Updated, FOptionalString CrmLink, FOptionalInt64 Created, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break Customer", meta=(NativeBreakFunc))
	static void Break(const UCustomer* Serializable, FString& Name, FBeamCid& Cid, TArray<UProject*>& Projects, TArray<URealmsBasicAccount*>& Accounts, FOptionalString& PaymentStatus, FOptionalString& Image, FOptionalString& Contact, FOptionalString& Alias, FOptionalInt64& Updated, FOptionalString& CrmLink, FOptionalInt64& Created);
};