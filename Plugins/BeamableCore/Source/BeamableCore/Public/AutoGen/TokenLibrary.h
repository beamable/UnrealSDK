
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Token.h"

#include "TokenLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTokenLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - Token To JSON String")
	static FString TokenToJsonString(const UToken* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make Token", meta=(DefaultToSelf="Outer", AdvancedDisplay="GamerTag, AccountId, Pid, ExpiresMs, Platform, Device, bRevoked, Scopes, Outer", NativeMakeFunc))
	static UToken* Make(int64 Cid, FString Token, FString Type, int64 Created, FOptionalInt64 GamerTag, FOptionalInt64 AccountId, FOptionalString Pid, FOptionalInt64 ExpiresMs, FOptionalString Platform, FOptionalString Device, FOptionalBool bRevoked, FOptionalArrayOfString Scopes, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break Token", meta=(NativeBreakFunc))
	static void Break(const UToken* Serializable, int64& Cid, FString& Token, FString& Type, int64& Created, FOptionalInt64& GamerTag, FOptionalInt64& AccountId, FOptionalString& Pid, FOptionalInt64& ExpiresMs, FOptionalString& Platform, FOptionalString& Device, FOptionalBool& bRevoked, FOptionalArrayOfString& Scopes);
};