
#include "BeamableCore/Public/AutoGen/FriendLibrary.h"

#include "CoreMinimal.h"


FString UFriendLibrary::FriendToJsonString(const UFriend* Serializable, const bool Pretty)
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

UFriend* UFriendLibrary::Make(FBeamGamerTag PlayerId, EFriendSource Source, UObject* Outer)
{
	auto Serializable = NewObject<UFriend>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->Source = Source;
	
	return Serializable;
}

void UFriendLibrary::Break(const UFriend* Serializable, FBeamGamerTag& PlayerId, EFriendSource& Source)
{
	PlayerId = Serializable->PlayerId;
	Source = Serializable->Source;
		
}

