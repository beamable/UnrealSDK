#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicCustomer.h"

#include "RealmsBasicCustomerLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmsBasicCustomerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="RealmsBasicCustomer To JSON String")
	static FString RealmsBasicCustomerToJsonString(const URealmsBasicCustomer* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make RealmsBasicCustomer", meta=(DefaultToSelf="Outer", AdvancedDisplay="ActivationStatus, PaymentStatus, Image, Contact, Alias, Updated, CrmLink, Created, Outer", NativeMakeFunc))
	static URealmsBasicCustomer* Make(FString Name, FBeamCid Cid, TArray<UProject*> Projects, TArray<URealmsBasicAccount*> Accounts, FOptionalString ActivationStatus, FOptionalString PaymentStatus, FOptionalString Image, FOptionalString Contact, FOptionalString Alias, FOptionalInt64 Updated, FOptionalString CrmLink, FOptionalInt64 Created, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break RealmsBasicCustomer", meta=(NativeBreakFunc))
	static void Break(const URealmsBasicCustomer* Serializable, FString& Name, FBeamCid& Cid, TArray<UProject*>& Projects, TArray<URealmsBasicAccount*>& Accounts, FOptionalString& ActivationStatus, FOptionalString& PaymentStatus, FOptionalString& Image, FOptionalString& Contact, FOptionalString& Alias, FOptionalInt64& Updated, FOptionalString& CrmLink, FOptionalInt64& Created);
};