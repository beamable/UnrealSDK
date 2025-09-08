
#include "BeamableCore/Public/AutoGen/AdminActorInFlightMessageLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAdminActorInFlightMessageLibrary::AdminActorInFlightMessageToJsonString(const UAdminActorInFlightMessage* Serializable, const bool Pretty)
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

UAdminActorInFlightMessage* UAdminActorInFlightMessageLibrary::Make(FString Service, FString MessageId, FString Method, FString Path, FString Body, FOptionalBool bLimitFailureRetries, FOptionalString Shard, FOptionalInt64 GamerTag, UObject* Outer)
{
	auto Serializable = NewObject<UAdminActorInFlightMessage>(Outer);
	Serializable->Service = Service;
	Serializable->MessageId = MessageId;
	Serializable->Method = Method;
	Serializable->Path = Path;
	Serializable->Body = Body;
	Serializable->bLimitFailureRetries = bLimitFailureRetries;
	Serializable->Shard = Shard;
	Serializable->GamerTag = GamerTag;
	
	return Serializable;
}

void UAdminActorInFlightMessageLibrary::Break(const UAdminActorInFlightMessage* Serializable, FString& Service, FString& MessageId, FString& Method, FString& Path, FString& Body, FOptionalBool& bLimitFailureRetries, FOptionalString& Shard, FOptionalInt64& GamerTag)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Service = Serializable->Service;
		MessageId = Serializable->MessageId;
		Method = Serializable->Method;
		Path = Serializable->Path;
		Body = Serializable->Body;
		bLimitFailureRetries = Serializable->bLimitFailureRetries;
		Shard = Serializable->Shard;
		GamerTag = Serializable->GamerTag;
	}
		
}

