#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/ListAuditResponse.h"

#include "ListAuditResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UListAuditResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ListAuditResponse To JSON String")
	static FString ListAuditResponseToJsonString(const UListAuditResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ListAuditResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UListAuditResponse* Make(TArray<UPaymentAuditEntryViewModel*> Audits, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ListAuditResponse", meta=(NativeBreakFunc))
	static void Break(const UListAuditResponse* Serializable, TArray<UPaymentAuditEntryViewModel*>& Audits);
};