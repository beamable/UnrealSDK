
#include "BeamableCore/Public/AutoGen/FriendLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UFriendLibrary::FriendToJsonString(const UFriend* Serializable, const bool Pretty)
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

UFriend* UFriendLibrary::Make(FBeamGamerTag PlayerId, EBeamFriendSource Source, UObject* Outer)
{
	auto Serializable = NewObject<UFriend>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->Source = Source;
	
	return Serializable;
}

void UFriendLibrary::Break(const UFriend* Serializable, FBeamGamerTag& PlayerId, EBeamFriendSource& Source)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
		Source = Serializable->Source;
	}
		
}

