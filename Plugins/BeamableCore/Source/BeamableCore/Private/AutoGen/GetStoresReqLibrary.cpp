
#include "BeamableCore/Public/AutoGen/GetStoresReqLibrary.h"

#include "CoreMinimal.h"


FString UGetStoresReqLibrary::GetStoresReqToJsonString(const UGetStoresReq* Serializable, const bool Pretty)
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

UGetStoresReq* UGetStoresReqLibrary::Make(FOptionalString Scope, UObject* Outer)
{
	auto Serializable = NewObject<UGetStoresReq>(Outer);
	Serializable->Scope = Scope;
	
	return Serializable;
}

void UGetStoresReqLibrary::Break(const UGetStoresReq* Serializable, FOptionalString& Scope)
{
	Scope = Serializable->Scope;
		
}

