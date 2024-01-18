
#include "BeamableCore/Public/AutoGen/RegisterReqLibrary.h"

#include "CoreMinimal.h"


FString URegisterReqLibrary::RegisterReqToJsonString(const URegisterReq* Serializable, const bool Pretty)
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

URegisterReq* URegisterReqLibrary::Make(FString Provider, FString Token, UObject* Outer)
{
	auto Serializable = NewObject<URegisterReq>(Outer);
	Serializable->Provider = Provider;
	Serializable->Token = Token;
	
	return Serializable;
}

void URegisterReqLibrary::Break(const URegisterReq* Serializable, FString& Provider, FString& Token)
{
	Provider = Serializable->Provider;
	Token = Serializable->Token;
		
}

