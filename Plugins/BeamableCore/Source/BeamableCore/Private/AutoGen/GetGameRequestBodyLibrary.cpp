
#include "AutoGen/GetGameRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UGetGameRequestBodyLibrary::GetGameRequestBodyToJsonString(const UGetGameRequestBody* Serializable, const bool Pretty)
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

UGetGameRequestBody* UGetGameRequestBodyLibrary::Make(FString RootPID, UObject* Outer)
{
	auto Serializable = NewObject<UGetGameRequestBody>(Outer);
	Serializable->RootPID = RootPID;
	
	return Serializable;
}

void UGetGameRequestBodyLibrary::Break(const UGetGameRequestBody* Serializable, FString& RootPID)
{
	RootPID = Serializable->RootPID;
		
}

