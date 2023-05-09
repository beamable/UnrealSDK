#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetProductsResponse.h"

#include "GetProductsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetProductsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetProductsResponse To JSON String")
	static FString GetProductsResponseToJsonString(const UGetProductsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetProductsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetProductsResponse* Make(TArray<UProductView*> Products, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetProductsResponse", meta=(NativeBreakFunc))
	static void Break(const UGetProductsResponse* Serializable, TArray<UProductView*>& Products);
};