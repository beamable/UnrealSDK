
#include "BeamableCore/Public/AutoGen/InFlightMessageLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UInFlightMessageLibrary::InFlightMessageToJsonString(const UInFlightMessage* Serializable, const bool Pretty)
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

UInFlightMessage* UInFlightMessageLibrary::Make(FString Method, FString Body, FString Path, FString Service, FString Id, FOptionalBool bLimitFailureRetries, FOptionalInt64 GamerTag, FOptionalString Shard, UObject* Outer)
{
	auto Serializable = NewObject<UInFlightMessage>(Outer);
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

void UInFlightMessageLibrary::Break(const UInFlightMessage* Serializable, FString& Method, FString& Body, FString& Path, FString& Service, FString& Id, FOptionalBool& bLimitFailureRetries, FOptionalInt64& GamerTag, FOptionalString& Shard)
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

