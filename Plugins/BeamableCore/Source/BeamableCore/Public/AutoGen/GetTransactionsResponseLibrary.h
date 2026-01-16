#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetTransactionsResponse.h"

#include "GetTransactionsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetTransactionsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Json", DisplayName="GetTransactionsResponse To JSON String")
	static FString GetTransactionsResponseToJsonString(const UGetTransactionsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Make/Break", DisplayName="Make GetTransactionsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Transactions, Outer", NativeMakeFunc))
	static UGetTransactionsResponse* Make(FOptionalArrayOfTransaction Transactions, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Make/Break", DisplayName="Break GetTransactionsResponse", meta=(NativeBreakFunc))
	static void Break(const UGetTransactionsResponse* Serializable, FOptionalArrayOfTransaction& Transactions);
};