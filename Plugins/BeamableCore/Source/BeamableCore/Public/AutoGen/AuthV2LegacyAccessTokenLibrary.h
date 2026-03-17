#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2LegacyAccessToken.h"

#include "AuthV2LegacyAccessTokenLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2LegacyAccessTokenLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2LegacyAccessToken To JSON String")
	static FString AuthV2LegacyAccessTokenToJsonString(const UAuthV2LegacyAccessToken* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2LegacyAccessToken", meta=(DefaultToSelf="Outer", AdvancedDisplay="bRevoked, Ttl, AccountIdRaw, Cid, GamerTag, Created, Type, ExpiresMs, DeviceId, Platform, Token, CustomerId, GameId, RealmId, AccountId, PlayerId, Outer", NativeMakeFunc))
	static UAuthV2LegacyAccessToken* Make(FOptionalBool bRevoked, FOptionalDateTime Ttl, FOptionalInt64 AccountIdRaw, FOptionalInt64 Cid, FOptionalInt64 GamerTag, FOptionalDateTime Created, FOptionalString Type, FOptionalInt64 ExpiresMs, FOptionalString DeviceId, FOptionalString Platform, FOptionalString Token, FOptionalString CustomerId, FOptionalString GameId, FOptionalString RealmId, FOptionalString AccountId, FOptionalString PlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2LegacyAccessToken", meta=(NativeBreakFunc))
	static void Break(const UAuthV2LegacyAccessToken* Serializable, FOptionalBool& bRevoked, FOptionalDateTime& Ttl, FOptionalInt64& AccountIdRaw, FOptionalInt64& Cid, FOptionalInt64& GamerTag, FOptionalDateTime& Created, FOptionalString& Type, FOptionalInt64& ExpiresMs, FOptionalString& DeviceId, FOptionalString& Platform, FOptionalString& Token, FOptionalString& CustomerId, FOptionalString& GameId, FOptionalString& RealmId, FOptionalString& AccountId, FOptionalString& PlayerId);
};