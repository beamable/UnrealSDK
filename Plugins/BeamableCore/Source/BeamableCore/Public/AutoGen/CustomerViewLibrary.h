#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/CustomerView.h"

#include "CustomerViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCustomerViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - CustomerView To JSON String")
	static FString CustomerViewToJsonString(const UCustomerView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make CustomerView", meta=(DefaultToSelf="Outer", AdvancedDisplay="Alias, Outer", NativeMakeFunc))
	static UCustomerView* Make(FBeamCid Cid, FString Name, TArray<UProjectView*> Projects, FOptionalString Alias, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break CustomerView", meta=(NativeBreakFunc))
	static void Break(const UCustomerView* Serializable, FBeamCid& Cid, FString& Name, TArray<UProjectView*>& Projects, FOptionalString& Alias);
};