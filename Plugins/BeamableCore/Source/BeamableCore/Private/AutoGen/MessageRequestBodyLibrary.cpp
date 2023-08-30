
#include "BeamableCore/Public/AutoGen/MessageRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UMessageRequestBodyLibrary::MessageRequestBodyToJsonString(const UMessageRequestBody* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UMessageRequestBody* UMessageRequestBodyLibrary::Make(FOptionalString Body, FOptionalString Cid, FOptionalString Pid, FOptionalString PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<UMessageRequestBody>(Outer);
	Serializable->Body = Body;
	Serializable->Cid = Cid;
	Serializable->Pid = Pid;
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void UMessageRequestBodyLibrary::Break(const UMessageRequestBody* Serializable, FOptionalString& Body, FOptionalString& Cid, FOptionalString& Pid, FOptionalString& PlayerId)
{
	Body = Serializable->Body;
	Cid = Serializable->Cid;
	Pid = Serializable->Pid;
	PlayerId = Serializable->PlayerId;
		
}

