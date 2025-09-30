#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicCustomerView.h"

#include "RealmsBasicCustomerViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmsBasicCustomerViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="RealmsBasicCustomerView To JSON String")
	static FString RealmsBasicCustomerViewToJsonString(const URealmsBasicCustomerView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make RealmsBasicCustomerView", meta=(DefaultToSelf="Outer", AdvancedDisplay="Alias, Outer", NativeMakeFunc))
	static URealmsBasicCustomerView* Make(FBeamCid Cid, FString Name, TArray<UProjectView*> Projects, FOptionalString Alias, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break RealmsBasicCustomerView", meta=(NativeBreakFunc))
	static void Break(const URealmsBasicCustomerView* Serializable, FBeamCid& Cid, FString& Name, TArray<UProjectView*>& Projects, FOptionalString& Alias);
};