
#include "BeamableCore/Public/AutoGen/AccountsBasicInFlightMessageLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAccountsBasicInFlightMessageLibrary::AccountsBasicInFlightMessageToJsonString(const UAccountsBasicInFlightMessage* Serializable, const bool Pretty)
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

UAccountsBasicInFlightMessage* UAccountsBasicInFlightMessageLibrary::Make(FString Method, FString Body, FString Path, FString Service, FString Id, FOptionalBool bLimitFailureRetries, FOptionalInt64 GamerTag, FOptionalString Shard, UObject* Outer)
{
	auto Serializable = NewObject<UAccountsBasicInFlightMessage>(Outer);
	Serializable->Method = Method;
	Serializable->Body = Body;
	Serializable->Path = Path;
	Serializable->Service = Service;
	Serializable->Id = Id;
	Serializable->bLimitFailureRetries = bLimitFailureRetries;
	Serializable->GamerTag = GamerTag;
	Serializable->Shard = Shard;
	
	return Serializable;
}

void UAccountsBasicInFlightMessageLibrary::Break(const UAccountsBasicInFlightMessage* Serializable, FString& Method, FString& Body, FString& Path, FString& Service, FString& Id, FOptionalBool& bLimitFailureRetries, FOptionalInt64& GamerTag, FOptionalString& Shard)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Method = Serializable->Method;
		Body = Serializable->Body;
		Path = Serializable->Path;
		Service = Serializable->Service;
		Id = Serializable->Id;
		bLimitFailureRetries = Serializable->bLimitFailureRetries;
		GamerTag = Serializable->GamerTag;
		Shard = Serializable->Shard;
	}
		
}

