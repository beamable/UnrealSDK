#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2RefreshToken.h"

#include "AuthV2RefreshTokenLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2RefreshTokenLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2RefreshToken To JSON String")
	static FString AuthV2RefreshTokenToJsonString(const UAuthV2RefreshToken* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2RefreshToken", meta=(DefaultToSelf="Outer", AdvancedDisplay="bRevoked, Ttl, AccountIdRaw, Cid, GamerTag, Created, Type, ExpiresMs, DeviceId, Platform, Token, CustomerId, GameId, RealmId, AccountId, PlayerId, Outer", NativeMakeFunc))
	static UAuthV2RefreshToken* Make(FOptionalBool bRevoked, FOptionalDateTime Ttl, FOptionalInt64 AccountIdRaw, FOptionalInt64 Cid, FOptionalInt64 GamerTag, FOptionalDateTime Created, FOptionalString Type, FOptionalInt64 ExpiresMs, FOptionalString DeviceId, FOptionalString Platform, FOptionalString Token, FOptionalString CustomerId, FOptionalString GameId, FOptionalString RealmId, FOptionalString AccountId, FOptionalString PlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2RefreshToken", meta=(NativeBreakFunc))
	static void Break(const UAuthV2RefreshToken* Serializable, FOptionalBool& bRevoked, FOptionalDateTime& Ttl, FOptionalInt64& AccountIdRaw, FOptionalInt64& Cid, FOptionalInt64& GamerTag, FOptionalDateTime& Created, FOptionalString& Type, FOptionalInt64& ExpiresMs, FOptionalString& DeviceId, FOptionalString& Platform, FOptionalString& Token, FOptionalString& CustomerId, FOptionalString& GameId, FOptionalString& RealmId, FOptionalString& AccountId, FOptionalString& PlayerId);
};