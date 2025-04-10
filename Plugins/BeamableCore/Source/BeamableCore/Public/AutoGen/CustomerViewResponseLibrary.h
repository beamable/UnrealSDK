#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CustomerViewResponse.h"

#include "CustomerViewResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCustomerViewResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="CustomerViewResponse To JSON String")
	static FString CustomerViewResponseToJsonString(const UCustomerViewResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make CustomerViewResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCustomerViewResponse* Make(UCustomerView* Customer, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break CustomerViewResponse", meta=(NativeBreakFunc))
	static void Break(const UCustomerViewResponse* Serializable, UCustomerView*& Customer);
};