
#include "AutoGen/RoomInfoLibrary.h"

#include "CoreMinimal.h"


FString URoomInfoLibrary::RoomInfoToJsonString(const URoomInfo* Serializable, const bool Pretty)
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

URoomInfo* URoomInfoLibrary::Make(bool bKeepSubscribed, FString Id, FString Name, FOptionalArrayOfInt64 Players, UObject* Outer)
{
	auto Serializable = NewObject<URoomInfo>(Outer);
	Serializable->bKeepSubscribed = bKeepSubscribed;
	Serializable->Id = Id;
	Serializable->Name = Name;
	Serializable->Players = Players;
	
	return Serializable;
}

void URoomInfoLibrary::Break(const URoomInfo* Serializable, bool& bKeepSubscribed, FString& Id, FString& Name, FOptionalArrayOfInt64& Players)
{
	bKeepSubscribed = Serializable->bKeepSubscribed;
	Id = Serializable->Id;
	Name = Serializable->Name;
	Players = Serializable->Players;
		
}

