
#include "BeamableCore/Public/AutoGen/ImportFriendsRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UImportFriendsRequestBodyLibrary::ImportFriendsRequestBodyToJsonString(const UImportFriendsRequestBody* Serializable, const bool Pretty)
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

UImportFriendsRequestBody* UImportFriendsRequestBodyLibrary::Make(FString Source, FString Token, UObject* Outer)
{
	auto Serializable = NewObject<UImportFriendsRequestBody>(Outer);
	Serializable->Source = Source;
	Serializable->Token = Token;
	
	return Serializable;
}

void UImportFriendsRequestBodyLibrary::Break(const UImportFriendsRequestBody* Serializable, FString& Source, FString& Token)
{
	Source = Serializable->Source;
	Token = Serializable->Token;
		
}

