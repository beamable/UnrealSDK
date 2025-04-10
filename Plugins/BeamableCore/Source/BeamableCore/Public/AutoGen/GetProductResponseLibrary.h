#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetProductResponse.h"

#include "GetProductResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetProductResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payments|4 - Json", DisplayName="GetProductResponse To JSON String")
	static FString GetProductResponseToJsonString(const UGetProductResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|3 - Backend", DisplayName="Make GetProductResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetProductResponse* Make(FString Id, FString Name, FString Description, int32 Price, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|3 - Backend", DisplayName="Break GetProductResponse", meta=(NativeBreakFunc))
	static void Break(const UGetProductResponse* Serializable, FString& Id, FString& Name, FString& Description, int32& Price);
};