#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CustomerActorCustomerView.h"

#include "CustomerActorCustomerViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCustomerActorCustomerViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="CustomerActorCustomerView To JSON String")
	static FString CustomerActorCustomerViewToJsonString(const UCustomerActorCustomerView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make CustomerActorCustomerView", meta=(DefaultToSelf="Outer", AdvancedDisplay="Alias, Realms, Outer", NativeMakeFunc))
	static UCustomerActorCustomerView* Make(FString CustomerId, FString Name, FOptionalString Alias, FOptionalArrayOfRealmView Realms, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break CustomerActorCustomerView", meta=(NativeBreakFunc))
	static void Break(const UCustomerActorCustomerView* Serializable, FString& CustomerId, FString& Name, FOptionalString& Alias, FOptionalArrayOfRealmView& Realms);
};