#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ListAuditRequestBody.h"

#include "ListAuditRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UListAuditRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Json", DisplayName="ListAuditRequestBody To JSON String")
	static FString ListAuditRequestBodyToJsonString(const UListAuditRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make ListAuditRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Providerid, Provider, State, Txid, Player, Start, Limit, Outer", NativeMakeFunc))
	static UListAuditRequestBody* Make(FOptionalString Providerid, FOptionalString Provider, FOptionalString State, FOptionalInt64 Txid, FOptionalInt64 Player, FOptionalInt32 Start, FOptionalInt32 Limit, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Break ListAuditRequestBody", meta=(NativeBreakFunc))
	static void Break(const UListAuditRequestBody* Serializable, FOptionalString& Providerid, FOptionalString& Provider, FOptionalString& State, FOptionalInt64& Txid, FOptionalInt64& Player, FOptionalInt32& Start, FOptionalInt32& Limit);
};