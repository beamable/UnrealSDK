#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicCustomersResponse.h"

#include "RealmsBasicCustomersResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmsBasicCustomersResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="RealmsBasicCustomersResponse To JSON String")
	static FString RealmsBasicCustomersResponseToJsonString(const URealmsBasicCustomersResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make RealmsBasicCustomersResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URealmsBasicCustomersResponse* Make(TArray<URealmsBasicCustomer*> Result, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break RealmsBasicCustomersResponse", meta=(NativeBreakFunc))
	static void Break(const URealmsBasicCustomersResponse* Serializable, TArray<URealmsBasicCustomer*>& Result);
};