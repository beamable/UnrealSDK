
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

UInFlightMessage* UInFlightMessageLibrary::Make(FString Service, FString Id, FString Method, FString Path, FString Body, FOptionalBool bLimitFailureRetries, FOptionalString Shard, FOptionalInt64 GamerTag, UObject* Outer)
{
	auto Serializable = NewObject<UInFlightMessage>(Outer);
	Serializable->Service = Service;
	Serializable->Id = Id;
	Serializable->Method = Method;
	Serializable->Path = Path;
	Serializable->Body = Body;
	Serializable->bLimitFailureRetries = bLimitFailureRetries;
	Serializable->Shard = Shard;
	Serializable->GamerTag = GamerTag;
	
	return Serializable;
}

void UInFlightMessageLibrary::Break(const UInFlightMessage* Serializable, FString& Service, FString& Id, FString& Method, FString& Path, FString& Body, FOptionalBool& bLimitFailureRetries, FOptionalString& Shard, FOptionalInt64& GamerTag)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Service = Serializable->Service;
		Id = Serializable->Id;
		Method = Serializable->Method;
		Path = Serializable->Path;
		Body = Serializable->Body;
		bLimitFailureRetries = Serializable->bLimitFailureRetries;
		Shard = Serializable->Shard;
		GamerTag = Serializable->GamerTag;
	}
		
}

