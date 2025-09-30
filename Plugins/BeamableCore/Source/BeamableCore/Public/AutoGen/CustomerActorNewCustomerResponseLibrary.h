#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CustomerActorNewCustomerResponse.h"

#include "CustomerActorNewCustomerResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCustomerActorNewCustomerResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="CustomerActorNewCustomerResponse To JSON String")
	static FString CustomerActorNewCustomerResponseToJsonString(const UCustomerActorNewCustomerResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make CustomerActorNewCustomerResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="bActivationPending, Alias, Outer", NativeMakeFunc))
	static UCustomerActorNewCustomerResponse* Make(UAuthResponse* Token, FString CustomerId, FString RealmId, FString Name, FString RealmName, FOptionalBool bActivationPending, FOptionalString Alias, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break CustomerActorNewCustomerResponse", meta=(NativeBreakFunc))
	static void Break(const UCustomerActorNewCustomerResponse* Serializable, UAuthResponse*& Token, FString& CustomerId, FString& RealmId, FString& Name, FString& RealmName, FOptionalBool& bActivationPending, FOptionalString& Alias);
};