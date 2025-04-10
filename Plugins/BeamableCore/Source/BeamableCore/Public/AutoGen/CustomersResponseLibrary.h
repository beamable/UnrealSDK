#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CustomersResponse.h"

#include "CustomersResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCustomersResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|4 - Json", DisplayName="CustomersResponse To JSON String")
	static FString CustomersResponseToJsonString(const UCustomersResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|3 - Backend", DisplayName="Make CustomersResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCustomersResponse* Make(TArray<UCustomer*> Result, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|3 - Backend", DisplayName="Break CustomersResponse", meta=(NativeBreakFunc))
	static void Break(const UCustomersResponse* Serializable, TArray<UCustomer*>& Result);
};