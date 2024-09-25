#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/SKU.h"

#include "SKULibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USKULibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - SKU To JSON String")
	static FString SKUToJsonString(const USKU* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make SKU", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USKU* Make(FString Name, FString Description, int32 RealPrice, TMap<FString, FString> ProductIds, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break SKU", meta=(NativeBreakFunc))
	static void Break(const USKU* Serializable, FString& Name, FString& Description, int32& RealPrice, TMap<FString, FString>& ProductIds);
};