
#include "BeamableCore/Public/AutoGen/LobbyPlayerLibrary.h"

#include "CoreMinimal.h"


FString ULobbyPlayerLibrary::LobbyPlayerToJsonString(const ULobbyPlayer* Serializable, const bool Pretty)
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

ULobbyPlayer* ULobbyPlayerLibrary::Make(FOptionalString PlayerId, FOptionalString Joined, FOptionalArrayOfTag Tags, UObject* Outer)
{
	auto Serializable = NewObject<ULobbyPlayer>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->Joined = Joined;
	Serializable->Tags = Tags;
	
	return Serializable;
}

void ULobbyPlayerLibrary::Break(const ULobbyPlayer* Serializable, FOptionalString& PlayerId, FOptionalString& Joined, FOptionalArrayOfTag& Tags)
{
	PlayerId = Serializable->PlayerId;
	Joined = Serializable->Joined;
	Tags = Serializable->Tags;
		
}

