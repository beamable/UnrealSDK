
#include "BeamableCore/Public/AutoGen/OtelAuthConfigLibrary.h"

#include "CoreMinimal.h"


FString UOtelAuthConfigLibrary::OtelAuthConfigToJsonString(const UOtelAuthConfig* Serializable, const bool Pretty)
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

UOtelAuthConfig* UOtelAuthConfigLibrary::Make(FString Endpoint, FString Username, FString Password, FOptionalDateTime ExpiresAt, UObject* Outer)
{
	auto Serializable = NewObject<UOtelAuthConfig>(Outer);
	Serializable->Endpoint = Endpoint;
	Serializable->Username = Username;
	Serializable->Password = Password;
	Serializable->ExpiresAt = ExpiresAt;
	
	return Serializable;
}

void UOtelAuthConfigLibrary::Break(const UOtelAuthConfig* Serializable, FString& Endpoint, FString& Username, FString& Password, FOptionalDateTime& ExpiresAt)
{
	Endpoint = Serializable->Endpoint;
	Username = Serializable->Username;
	Password = Serializable->Password;
	ExpiresAt = Serializable->ExpiresAt;
		
}

