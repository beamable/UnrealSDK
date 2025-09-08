#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ApiCustomersActivatePutCustomerResponse.h"

#include "ApiCustomersActivatePutCustomerResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UApiCustomersActivatePutCustomerResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="ApiCustomersActivatePutCustomerResponse To JSON String")
	static FString ApiCustomersActivatePutCustomerResponseToJsonString(const UApiCustomersActivatePutCustomerResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make ApiCustomersActivatePutCustomerResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UApiCustomersActivatePutCustomerResponse* Make(UObject* Outer);

	
};