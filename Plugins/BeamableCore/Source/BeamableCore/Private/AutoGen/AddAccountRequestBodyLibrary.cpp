
#include "BeamableCore/Public/AutoGen/AddAccountRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UAddAccountRequestBodyLibrary::AddAccountRequestBodyToJsonString(const UAddAccountRequestBody* Serializable, const bool Pretty)
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

UAddAccountRequestBody* UAddAccountRequestBodyLibrary::Make(FString Email, FOptionalString Role, UObject* Outer)
{
	auto Serializable = NewObject<UAddAccountRequestBody>(Outer);
	Serializable->Email = Email;
	Serializable->Role = Role;
	
	return Serializable;
}

void UAddAccountRequestBodyLibrary::Break(const UAddAccountRequestBody* Serializable, FString& Email, FOptionalString& Role)
{
	Email = Serializable->Email;
	Role = Serializable->Role;
		
}

