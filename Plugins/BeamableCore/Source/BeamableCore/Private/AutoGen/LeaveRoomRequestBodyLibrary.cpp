
#include "AutoGen/LeaveRoomRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString ULeaveRoomRequestBodyLibrary::LeaveRoomRequestBodyToJsonString(const ULeaveRoomRequestBody* Serializable, const bool Pretty)
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

ULeaveRoomRequestBody* ULeaveRoomRequestBodyLibrary::Make(FString RoomId, UObject* Outer)
{
	auto Serializable = NewObject<ULeaveRoomRequestBody>(Outer);
	Serializable->RoomId = RoomId;
	
	return Serializable;
}

void ULeaveRoomRequestBodyLibrary::Break(const ULeaveRoomRequestBody* Serializable, FString& RoomId)
{
	RoomId = Serializable->RoomId;
		
}
