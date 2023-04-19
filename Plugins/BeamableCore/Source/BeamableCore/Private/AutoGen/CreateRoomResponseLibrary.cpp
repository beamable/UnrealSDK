
#include "BeamableCore/Public/AutoGen/CreateRoomResponseLibrary.h"

#include "CoreMinimal.h"


FString UCreateRoomResponseLibrary::CreateRoomResponseToJsonString(const UCreateRoomResponse* Serializable, const bool Pretty)
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

UCreateRoomResponse* UCreateRoomResponseLibrary::Make(URoomInfo* Room, UObject* Outer)
{
	auto Serializable = NewObject<UCreateRoomResponse>(Outer);
	Serializable->Room = Room;
	
	return Serializable;
}

void UCreateRoomResponseLibrary::Break(const UCreateRoomResponse* Serializable, URoomInfo*& Room)
{
	Room = Serializable->Room;
		
}

