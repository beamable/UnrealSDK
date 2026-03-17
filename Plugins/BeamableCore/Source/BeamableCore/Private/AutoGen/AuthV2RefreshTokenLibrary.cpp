
#include "BeamableCore/Public/AutoGen/AuthV2RefreshTokenLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2RefreshTokenLibrary::AuthV2RefreshTokenToJsonString(const UAuthV2RefreshToken* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UAuthV2RefreshToken* UAuthV2RefreshTokenLibrary::Make(FOptionalBool bRevoked, FOptionalDateTime Ttl, FOptionalInt64 AccountIdRaw, FOptionalInt64 Cid, FOptionalInt64 GamerTag, FOptionalDateTime Created, FOptionalString Type, FOptionalInt64 ExpiresMs, FOptionalString DeviceId, FOptionalString Platform, FOptionalString Token, FOptionalString CustomerId, FOptionalString GameId, FOptionalString RealmId, FOptionalString AccountId, FOptionalString PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2RefreshToken>(Outer);
	Serializable->bRevoked = bRevoked;
	Serializable->Ttl = Ttl;
	Serializable->AccountIdRaw = AccountIdRaw;
	Serializable->Cid = Cid;
	Serializable->GamerTag = GamerTag;
	Serializable->Created = Created;
	Serializable->Type = Type;
	Serializable->ExpiresMs = ExpiresMs;
	Serializable->DeviceId = DeviceId;
	Serializable->Platform = Platform;
	Serializable->Token = Token;
	Serializable->CustomerId = CustomerId;
	Serializable->GameId = GameId;
	Serializable->RealmId = RealmId;
	Serializable->AccountId = AccountId;
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void UAuthV2RefreshTokenLibrary::Break(const UAuthV2RefreshToken* Serializable, FOptionalBool& bRevoked, FOptionalDateTime& Ttl, FOptionalInt64& AccountIdRaw, FOptionalInt64& Cid, FOptionalInt64& GamerTag, FOptionalDateTime& Created, FOptionalString& Type, FOptionalInt64& ExpiresMs, FOptionalString& DeviceId, FOptionalString& Platform, FOptionalString& Token, FOptionalString& CustomerId, FOptionalString& GameId, FOptionalString& RealmId, FOptionalString& AccountId, FOptionalString& PlayerId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bRevoked = Serializable->bRevoked;
		Ttl = Serializable->Ttl;
		AccountIdRaw = Serializable->AccountIdRaw;
		Cid = Serializable->Cid;
		GamerTag = Serializable->GamerTag;
		Created = Serializable->Created;
		Type = Serializable->Type;
		ExpiresMs = Serializable->ExpiresMs;
		DeviceId = Serializable->DeviceId;
		Platform = Serializable->Platform;
		Token = Serializable->Token;
		CustomerId = Serializable->CustomerId;
		GameId = Serializable->GameId;
		RealmId = Serializable->RealmId;
		AccountId = Serializable->AccountId;
		PlayerId = Serializable->PlayerId;
	}
		
}

