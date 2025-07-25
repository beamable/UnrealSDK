
#include "BeamableCore/Public/AutoGen/ListAuditRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UListAuditRequestBodyLibrary::ListAuditRequestBodyToJsonString(const UListAuditRequestBody* Serializable, const bool Pretty)
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

UListAuditRequestBody* UListAuditRequestBodyLibrary::Make(FOptionalString Providerid, FOptionalString Provider, FOptionalString State, FOptionalInt64 Txid, FOptionalInt64 Player, FOptionalInt32 Start, FOptionalInt32 Limit, UObject* Outer)
{
	auto Serializable = NewObject<UListAuditRequestBody>(Outer);
	Serializable->Providerid = Providerid;
	Serializable->Provider = Provider;
	Serializable->State = State;
	Serializable->Txid = Txid;
	Serializable->Player = Player;
	Serializable->Start = Start;
	Serializable->Limit = Limit;
	
	return Serializable;
}

void UListAuditRequestBodyLibrary::Break(const UListAuditRequestBody* Serializable, FOptionalString& Providerid, FOptionalString& Provider, FOptionalString& State, FOptionalInt64& Txid, FOptionalInt64& Player, FOptionalInt32& Start, FOptionalInt32& Limit)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Providerid = Serializable->Providerid;
		Provider = Serializable->Provider;
		State = Serializable->State;
		Txid = Serializable->Txid;
		Player = Serializable->Player;
		Start = Serializable->Start;
		Limit = Serializable->Limit;
	}
		
}

