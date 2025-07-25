
#include "BeamableCore/Public/AutoGen/TokenLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTokenLibrary::TokenToJsonString(const UToken* Serializable, const bool Pretty)
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

UToken* UTokenLibrary::Make(FBeamCid Cid, FString Token, FString Type, int64 Created, FOptionalBeamGamerTag GamerTag, FOptionalBeamAccountId AccountId, FOptionalBeamPid Pid, FOptionalInt64 ExpiresMs, FOptionalString Platform, FOptionalString Device, FOptionalBool bRevoked, FOptionalArrayOfString Scopes, UObject* Outer)
{
	auto Serializable = NewObject<UToken>(Outer);
	Serializable->Cid = Cid;
	Serializable->Token = Token;
	Serializable->Type = Type;
	Serializable->Created = Created;
	Serializable->GamerTag = GamerTag;
	Serializable->AccountId = AccountId;
	Serializable->Pid = Pid;
	Serializable->ExpiresMs = ExpiresMs;
	Serializable->Platform = Platform;
	Serializable->Device = Device;
	Serializable->bRevoked = bRevoked;
	Serializable->Scopes = Scopes;
	
	return Serializable;
}

void UTokenLibrary::Break(const UToken* Serializable, FBeamCid& Cid, FString& Token, FString& Type, int64& Created, FOptionalBeamGamerTag& GamerTag, FOptionalBeamAccountId& AccountId, FOptionalBeamPid& Pid, FOptionalInt64& ExpiresMs, FOptionalString& Platform, FOptionalString& Device, FOptionalBool& bRevoked, FOptionalArrayOfString& Scopes)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Cid = Serializable->Cid;
		Token = Serializable->Token;
		Type = Serializable->Type;
		Created = Serializable->Created;
		GamerTag = Serializable->GamerTag;
		AccountId = Serializable->AccountId;
		Pid = Serializable->Pid;
		ExpiresMs = Serializable->ExpiresMs;
		Platform = Serializable->Platform;
		Device = Serializable->Device;
		bRevoked = Serializable->bRevoked;
		Scopes = Serializable->Scopes;
	}
		
}

