
#include "BeamableCore/Public/AutoGen/LeaveRoomResponseLibrary.h"

#include "CoreMinimal.h"


FString ULeaveRoomResponseLibrary::LeaveRoomResponseToJsonString(const ULeaveRoomResponse* Serializable, const bool Pretty)
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

ULeaveRoomResponse* ULeaveRoomResponseLibrary::Make(FString Removed, UObject* Outer)
{
	auto Serializable = NewObject<ULeaveRoomResponse>(Outer);
	Serializable->Removed = Removed;
	
	return Serializable;
}

void ULeaveRoomResponseLibrary::Break(const ULeaveRoomResponse* Serializable, FString& Removed)
{
	Removed = Serializable->Removed;
		
}

