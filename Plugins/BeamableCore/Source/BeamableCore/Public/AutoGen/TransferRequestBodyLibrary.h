#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TransferRequestBody.h"

#include "TransferRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTransferRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Json", DisplayName="TransferRequestBody To JSON String")
	static FString TransferRequestBodyToJsonString(const UTransferRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make TransferRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Transaction, Currencies, Outer", NativeMakeFunc))
	static UTransferRequestBody* Make(FBeamGamerTag RecipientPlayer, FOptionalString Transaction, FOptionalMapOfInt64 Currencies, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break TransferRequestBody", meta=(NativeBreakFunc))
	static void Break(const UTransferRequestBody* Serializable, FBeamGamerTag& RecipientPlayer, FOptionalString& Transaction, FOptionalMapOfInt64& Currencies);
};