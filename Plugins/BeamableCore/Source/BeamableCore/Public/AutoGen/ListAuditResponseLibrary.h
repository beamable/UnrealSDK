#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ListAuditResponse.h"

#include "ListAuditResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UListAuditResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|4 - Json", DisplayName="ListAuditResponse To JSON String")
	static FString ListAuditResponseToJsonString(const UListAuditResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|3 - Backend", DisplayName="Make ListAuditResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UListAuditResponse* Make(TArray<UPaymentAuditEntryViewModel*> Audits, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|3 - Backend", DisplayName="Break ListAuditResponse", meta=(NativeBreakFunc))
	static void Break(const UListAuditResponse* Serializable, TArray<UPaymentAuditEntryViewModel*>& Audits);
};