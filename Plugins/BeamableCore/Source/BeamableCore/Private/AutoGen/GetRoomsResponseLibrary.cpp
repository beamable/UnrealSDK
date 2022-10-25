
#include "AutoGen/GetRoomsResponseLibrary.h"

#include "CoreMinimal.h"


FString UGetRoomsResponseLibrary::GetRoomsResponseToJsonString(const UGetRoomsResponse* Serializable, const bool Pretty)
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

UGetRoomsResponse* UGetRoomsResponseLibrary::Make(TArray<URoomInfo*> Rooms, UObject* Outer)
{
	auto Serializable = NewObject<UGetRoomsResponse>(Outer);
	Serializable->Rooms = Rooms;
	
	return Serializable;
}

void UGetRoomsResponseLibrary::Break(const UGetRoomsResponse* Serializable, TArray<URoomInfo*>& Rooms)
{
	Rooms = Serializable->Rooms;
		
}

