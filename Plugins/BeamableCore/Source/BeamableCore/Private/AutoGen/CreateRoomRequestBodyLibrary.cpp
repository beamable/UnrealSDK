
#include "BeamableCore/Public/AutoGen/CreateRoomRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UCreateRoomRequestBodyLibrary::CreateRoomRequestBodyToJsonString(const UCreateRoomRequestBody* Serializable, const bool Pretty)
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

UCreateRoomRequestBody* UCreateRoomRequestBodyLibrary::Make(bool bKeepSubscribed, FString RoomName, TArray<int64> Players, UObject* Outer)
{
	auto Serializable = NewObject<UCreateRoomRequestBody>(Outer);
	Serializable->bKeepSubscribed = bKeepSubscribed;
	Serializable->RoomName = RoomName;
	Serializable->Players = Players;
	
	return Serializable;
}

void UCreateRoomRequestBodyLibrary::Break(const UCreateRoomRequestBody* Serializable, bool& bKeepSubscribed, FString& RoomName, TArray<int64>& Players)
{
	bKeepSubscribed = Serializable->bKeepSubscribed;
	RoomName = Serializable->RoomName;
	Players = Serializable->Players;
		
}

