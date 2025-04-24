#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeginPurchaseResponse.h"

#include "BeginPurchaseResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeginPurchaseResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Json", DisplayName="BeginPurchaseResponse To JSON String")
	static FString BeginPurchaseResponseToJsonString(const UBeginPurchaseResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make BeginPurchaseResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="AccessToken, Outer", NativeMakeFunc))
	static UBeginPurchaseResponse* Make(int64 Txid, FOptionalString AccessToken, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Break BeginPurchaseResponse", meta=(NativeBreakFunc))
	static void Break(const UBeginPurchaseResponse* Serializable, int64& Txid, FOptionalString& AccessToken);
};