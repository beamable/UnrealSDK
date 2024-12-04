
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetSamlpeStatRequestArgsLibrary.h"

#include "CoreMinimal.h"


FString UGetSamlpeStatRequestArgsLibrary::GetSamlpeStatRequestArgsToJsonString(const UGetSamlpeStatRequestArgs* Serializable, const bool Pretty)
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

UGetSamlpeStatRequestArgs* UGetSamlpeStatRequestArgsLibrary::Make(int64 UserID, UObject* Outer)
{
	auto Serializable = NewObject<UGetSamlpeStatRequestArgs>(Outer);
	Serializable->UserID = UserID;
	
	return Serializable;
}

void UGetSamlpeStatRequestArgsLibrary::Break(const UGetSamlpeStatRequestArgs* Serializable, int64& UserID)
{
	UserID = Serializable->UserID;
		
}

