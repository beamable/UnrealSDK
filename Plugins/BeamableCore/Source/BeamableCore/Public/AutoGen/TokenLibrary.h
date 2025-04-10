#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Token.h"

#include "TokenLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTokenLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="Token To JSON String")
	static FString TokenToJsonString(const UToken* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make Token", meta=(DefaultToSelf="Outer", AdvancedDisplay="GamerTag, AccountId, Pid, ExpiresMs, Platform, Device, bRevoked, Scopes, Outer", NativeMakeFunc))
	static UToken* Make(FBeamCid Cid, FString Token, FString Type, int64 Created, FOptionalBeamGamerTag GamerTag, FOptionalBeamAccountId AccountId, FOptionalBeamPid Pid, FOptionalInt64 ExpiresMs, FOptionalString Platform, FOptionalString Device, FOptionalBool bRevoked, FOptionalArrayOfString Scopes, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break Token", meta=(NativeBreakFunc))
	static void Break(const UToken* Serializable, FBeamCid& Cid, FString& Token, FString& Type, int64& Created, FOptionalBeamGamerTag& GamerTag, FOptionalBeamAccountId& AccountId, FOptionalBeamPid& Pid, FOptionalInt64& ExpiresMs, FOptionalString& Platform, FOptionalString& Device, FOptionalBool& bRevoked, FOptionalArrayOfString& Scopes);
};